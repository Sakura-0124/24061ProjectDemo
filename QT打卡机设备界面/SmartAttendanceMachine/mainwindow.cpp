#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QStandardItemModel>  // 添加 QStandardItemModel 头文件
#include <QStandardItem>       // 添加 QStandardItem 头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(new Database(this))
    , fingerprint(new FingerprintManager(this))
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
    // 导出考勤数据到Excel
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
