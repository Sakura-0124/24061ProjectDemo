#include "Register.h"
#include "ui_Register.h"
#include <QDebug>


Register::Register(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

//清除数据
void Register::resetWidget()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_acc->clear();
    ui->lineEdit_pass->clear();
    ui->lineEdit_pass2->clear();
}

void Register::on_pushButton_clicked()
{
    QSqlDatabase database;
    QSqlQuery dt(database);
    //获取文本数据
    QString id = ui->lineEdit_id->text();
    QString password = ui->lineEdit_pass->text();
    QString account = ui->lineEdit_acc->text();
    QString password2 = ui->lineEdit_pass2->text();
    //密码确定
    if (password != password2)
    {
        qDebug() << "密码不一致！！！" << endl;
        resetWidget();
        QMessageBox::critical(nullptr, "错误", "密码不一致，请重新输入！");
    } else {
        //实例化数据库对象
        AccountAndInfoDB *adb = AccountAndInfoDB::getInstance();
        //检查重复插入id
        dt.prepare(QString("SELECT * FROM Login WHERE id = :id"));
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
            adb->CreatAccountTable();
            adb->InsertAccount(id, account, password);
            QMessageBox::information(nullptr, "注册成功", "恭喜您，注册成功！");
            //注册成功跳转到管理员界面
            emit signalJumpWidget(JumpType::LOG);
        }
    }
}
//回退
void Register::on_pushButton_back_clicked()
{
    emit signalJumpWidget(JumpType::LOG);
}
