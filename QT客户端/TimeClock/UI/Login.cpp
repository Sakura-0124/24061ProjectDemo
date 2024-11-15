#include "Login.h"
#include "ui_Login.h"


Login::Login(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //gif图展示
    QMovie *movie = new QMovie(":/Image/4.gif");
    ui->label_movie->setMovie(movie);
    movie->start();
}

Login::~Login()
{
    delete ui;
}

//清除界面
void Login::resetWidget()
{
    ui->lineEdit_account->clear();
    ui->lineEdit_password->clear();
}

//登录转到槽
void Login::on_pushButton_2_clicked()
{
    //实例化操作数据库对象
    AccountAndInfoDB *adb = AccountAndInfoDB::getInstance();
    //创建账户表
    adb->CreatAccountTable();
    //创建数据库对象
    QSqlDatabase database;
    QSqlQuery dt(database);
    //获取文本信息
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    dt.prepare("SELECT * FROM Login WHERE account = :account AND password = :password");
    dt.bindValue(":account", account);
    dt.bindValue(":password", password);
    //进行校验
    if (dt.exec()) {
        if (dt.next()) {
            //成功跳转
            emit signalJumpWidget(JumpType::SEL);
        } else {
            // 登录失败，用户名或密码错误,弹出小窗口
            //第一个参数: 是父控件指针,第二个参数: 标题名称,第三个参数:信息提示框内容,
            //第四个参数: 信息提示框里面有多少个按钮，一般情况下默认为OK第五个参数: 指定按下Enter键时使用的按钮
            QMessageBox::critical(nullptr, "错误", "账号或密码错误，请重新输入！");
            //关掉小窗口后清除界面数据
            resetWidget();
        }
    } else {
        // SQL执行失败，打印错误信息
        qDebug() << "SQL Error:" << dt.lastError();
    }
    database.close();
}

//注册转到槽
void Login::on_pushButton_clicked()
{
    emit signalJumpWidget(JumpType::REG);
}
