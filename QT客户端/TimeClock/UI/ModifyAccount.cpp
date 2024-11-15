#include "ModifyAccount.h"
#include "ui_ModifyAccount.h"

ModifyAccount::ModifyAccount(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::ModifyAccount)
{
    ui->setupUi(this);
}

ModifyAccount::~ModifyAccount()
{
    delete ui;
}

//清除界面数据
void ModifyAccount::resetWidget()
{
    ui->lineEdit_modid->clear();
    ui->lineEdit_delid->clear();
    ui->lineEdit_oldpass->clear();
    ui->lineEdit_newpass->clear();
    ui->lineEdit_newpass2->clear();
}

//更改密码
void ModifyAccount::on_pushButton_mod_clicked()
{
    QSqlDatabase database;
    QSqlQuery dt(database);
    QString id = ui->lineEdit_modid->text();
    QString password = ui->lineEdit_oldpass->text();
    QString newpassword = ui->lineEdit_newpass->text();
    QString newpassword2 = ui->lineEdit_newpass2->text();
    //实例化数据库对象
    AccountAndInfoDB *adb = AccountAndInfoDB::getInstance();
    if (newpassword != newpassword2)
    {
        resetWidget();
        QMessageBox::critical(nullptr, "错误", "密码不一致，请重新输入！");
    } else {
        dt.prepare("SELECT * FROM Login WHERE id = :id AND password = :password");
        dt.bindValue(":id", id);
        dt.bindValue(":password", password);
        if (dt.exec()) {
            if (dt.next()) {
                adb->ModAccount(id, newpassword);
                QMessageBox::information(nullptr, "成功", "更改成功！");
                resetWidget();
            } else {
                QMessageBox::critical(nullptr, "错误", "旧密码不正确，请重新输入！");
                //关掉小窗口后清除界面数据
                resetWidget();
            }
        } else {
            // SQL执行失败，打印错误信息
            qDebug() << "SQL Error:" << dt.lastError();
        }
    }
}

//注销账号
void ModifyAccount::on_pushButton_del_clicked()
{
    QSqlDatabase database;
    QSqlQuery dt(database);
    QString id = ui->lineEdit_delid->text();
    //实例化数据库对象
    AccountAndInfoDB *adb = AccountAndInfoDB::getInstance();
    dt.prepare("SELECT * FROM Login WHERE id = :id");
    dt.bindValue(":id", id);
    if (dt.exec()) {
        if (dt.next()) {
            adb->DelAccount(id);
            QMessageBox::information(nullptr, "成功", "注销成功！");
            resetWidget();
        } else {
            QMessageBox::critical(nullptr, "错误", "用户不存在！");
            //关掉小窗口后清除界面数据
            resetWidget();
        }
    } else {
        // SQL执行失败，打印错误信息
        qDebug() << "SQL Error:" << dt.lastError();
    }
}
//回退
void ModifyAccount::on_pushButton_back_clicked()
{
    emit signalJumpWidget(JumpType::SEL);
}
