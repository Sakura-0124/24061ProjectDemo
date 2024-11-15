#include "Select.h"
#include "ui_Select.h"

Select::Select(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::Select)
{
    ui->setupUi(this);

    //设置ToolButton控件函数调用
    initToolButton();
}

Select::~Select()
{
    delete ui;
}

void Select::resetWidget()
{

}

//设置ToolButton控件
void Select::initToolButton()
{
    //《信息录入》
    //设置文字样式
    ui->toolButton_Infor->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //设置图片路径
    ui->toolButton_Infor->setIcon(QIcon(QString(":/Image/infor.png")));
    //设置图片大小
    ui->toolButton_Infor->setIconSize(QSize(30, 30));
    //设置文字信息
    ui->toolButton_Infor->setText("信息录入");

    //《考勤数据》
    ui->toolButton_AtDa->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolButton_AtDa->setIcon(QIcon(QString(":/Image/data.png")));
    ui->toolButton_AtDa->setIconSize(QSize(30, 30));
    ui->toolButton_AtDa->setText("考勤数据");

    //《信息管理》
    ui->toolButton_IM->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolButton_IM->setIcon(QIcon(QString(":/Image/im.png")));
    ui->toolButton_IM->setIconSize(QSize(30, 30));
    ui->toolButton_IM->setText("信息管理");

    //《员工删除》
    ui->toolButton_Del->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolButton_Del->setIcon(QIcon(QString(":/Image/del.png")));
    ui->toolButton_Del->setIconSize(QSize(30, 30));
    ui->toolButton_Del->setText("员工删除");

    //《账号更改》
    ui->toolButton_Mod->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolButton_Mod->setIcon(QIcon(QString(":/Image/reg.png")));
    ui->toolButton_Mod->setIconSize(QSize(30, 30));
    ui->toolButton_Mod->setText("账号更改");
}


//信息录入转到槽
void Select::on_toolButton_Infor_clicked()
{
    emit signalJumpWidget(JumpType::INFOR);
}

//考勤数据转到槽
void Select::on_toolButton_AtDa_clicked()
{
    emit signalJumpWidget(JumpType::ATDA);
}

//信息管理转到槽
void Select::on_toolButton_IM_clicked()
{
    emit signalJumpWidget(JumpType::IM);
}

//离职员工删除转到槽
void Select::on_toolButton_Del_clicked()
{
    emit signalJumpWidget(JumpType::DEL);
}

//账户修改转到槽
void Select::on_toolButton_Mod_clicked()
{
    emit signalJumpWidget(JumpType::MOD);
}
//回退
void Select::on_pushButton_back_clicked()
{
    emit signalJumpWidget(JumpType::LOG);
}
