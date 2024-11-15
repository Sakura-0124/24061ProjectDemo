#include "Information.h"
#include "ui_Information.h"
#include <QComboBox>
#include <QTcpSocket>

Information::Information(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);

    //设置comBoBox
    ui->comboBox->addItem("男");
    ui->comboBox->addItem("女");
    QFont font("Arial", 15); // 设置字体为Arial，大小为10
    ui->comboBox->setFont(font);
    ui->comboBox->setCurrentIndex(0); // 设置"选项1"为默认选项
}

Information::~Information()
{
    delete ui;
}

void Information::resetWidget()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_age->clear();
    ui->lineEdit_dep->clear();
}


//回退
void Information::on_pushButton_back_clicked()
{
    emit signalJumpWidget(JumpType::SEL);
}


//保存信息
void Information::on_pushButton_2_clicked()
{
    //创建数据库对象
    QSqlDatabase database;
    QSqlQuery dt(database);
    //获取文本信息
    QString id = ui->lineEdit_id->text();
    QString age = ui->lineEdit_age->text();
    QString name = ui->lineEdit_name->text();
    QString dep = ui->lineEdit_dep->text();
    QString sex = ui->comboBox->currentText();
    //实例化数据库对象
    AccountAndInfoDB *adb = AccountAndInfoDB::getInstance();
    //检查重复插入id
    dt.prepare(QString("SELECT * FROM Info WHERE id = :id"));
    dt.bindValue(":id", id);
    if (!dt.exec()) {
        qDebug() << "查询失败：" << dt.lastError();
    }
    if (dt.next())
    {
        QMessageBox::critical(nullptr, "错误", "用户已存在！！！");
        resetWidget();
    } else {
        //将注册的信息插入数据库
        adb->CreatInfoTable();
        adb->InsertInfo(id, name, age, sex, dep);
        QMessageBox::information(nullptr, "成功", "恭喜您，保存成功！");
        //注册成功清除数据
        resetWidget();
    }
}

//录入指纹信息发送
void Information::on_pushButton_clicked()
{

    //和服务器连接
    QTcpSocket socket;
    socket.connectToHost("192.168.3.61", 8080);
    if (socket.waitForConnected(3000)) // 等待连接建立，超时时间3秒
    {
        QString message = "录入指纹!";
        socket.write(message.toUtf8()); // 发送消息
        socket.waitForBytesWritten(3000); // 等待消息发送完成，超时时间3秒
        socket.waitForReadyRead(3000); // 等待响应，超时时间3秒
        qDebug() << "Received:" << socket.readAll(); // 读取响应
    }
    else
    {
        qDebug() << "Connection failed!";
    }
}
