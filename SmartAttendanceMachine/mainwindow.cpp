#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AttendanceQueryDialog.h"
#include <QTimer>
#include <QMessageBox>
#include <QStandardItemModel>  // 添加 QStandardItemModel 头文件
#include <QStandardItem>       // 添加 QStandardItem 头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(new Database(this))
    , fingerprint(new FingerprintManager(this))
    , serialHandler(new SerialPortHandler(this))
{
    ui->setupUi(this);

    // 每隔5秒刷新签到信息
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSignInInfo);
    timer->start(5000);

    // 导出按钮槽连接
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exportAttendanceData);
    // 指纹录入按钮槽连接
    connect(ui->fingerprintButton, &QPushButton::clicked, this, &MainWindow::enrollFingerprint);
    // 连接按钮的点击信号到槽函数
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);
    connect(ui->voiceRecognitionButton, &QPushButton::clicked, this, &MainWindow::on_voiceRecognitionButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSignInInfo()
{
    // 从数据库获取签到信息并在界面上更新
    auto attendanceList = database->getAttendanceList();
    // 更新ui->signInTableView，例如使用QStandardItemModel
    QStandardItemModel *model = new QStandardItemModel(attendanceList.size(), 3, this);
    model->setHorizontalHeaderLabels(QStringList() << "员工ID" << "姓名" << "签到时间");

    for (int i = 0; i < attendanceList.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(QString::number(attendanceList[i].employeeId)));
        model->setItem(i, 1, new QStandardItem(attendanceList[i].employeeName));
        model->setItem(i, 2, new QStandardItem(attendanceList[i].signInTime.toString()));
    }

    ui->signInTableView->setModel(model);
}

void MainWindow::exportAttendanceData()
{
    // 导出考勤数据为Excel
    if (database->exportToExcel()) {
        QMessageBox::information(this, "导出成功", "考勤数据已成功导出！");
    } else {
        QMessageBox::warning(this, "导出失败", "导出过程中出现错误。");
    }
}

void MainWindow::enrollFingerprint()
{
    // 调用指纹录入管理模块
    fingerprint->startEnrollment();
    ui->fingerprintStatusLabel->setText("指纹录入中...");
}

void MainWindow::onOpenButtonClicked() {
    QString portName = ui->portNameEdit->text();
    if (portName.isEmpty()) {
            qDebug() << "串口名为空，请输入有效的串口名。";
            return;
    }
    serialHandler->openPort(portName);
}

void MainWindow::onCloseButtonClicked() {
    serialHandler->closePort();
}

void MainWindow::onSendButtonClicked() {
    QString data = ui->dataEdit->text();
    serialHandler->sendData(data.toUtf8());
}

void MainWindow::on_voiceRecognitionButton_clicked()
{
    QProcess *process = new QProcess(this);
    QString program = "python";
    QStringList arguments;
    arguments << "speech_recognition.py";

    connect(process, &QProcess::readyReadStandardOutput, [process, this]() {
        QString output = process->readAllStandardOutput().trimmed();
        qDebug() << "Python recognition result:" << output;
        handleVoiceCommand(output);
    });

    process->start(program, arguments);
}

void MainWindow::handleVoiceCommand(const QString &command)
{
    if (command.contains("显示员工考勤")) {
        qDebug() << "执行显示员工考勤逻辑";
        // TODO: 在此处实现员工考勤显示逻辑
        ui->textBrowser->setText("显示某个员工的考勤信息...");
    } else if (command.contains("退出")) {
        qDebug() << "执行退出程序逻辑";
        close();  // 关闭程序
    } else {
        qDebug() << "未识别的命令: " << command;
        ui->textBrowser->setText("无法识别的命令，请重试。");
    }
}
