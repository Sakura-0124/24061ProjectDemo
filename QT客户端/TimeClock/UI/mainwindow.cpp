#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //开始是广告页面
    ui->stackedWidget->setCurrentIndex(JumpType::LOG);

    //信号与槽连接--for循环(省去很多连接时重复的步骤)
    //count 控件下面的页数
    for (int i = 0; i < ui->stackedWidget->count(); ++i){
        AbstructClass *abstruct =
                dynamic_cast<AbstructClass *>(ui->stackedWidget->widget(i));//通过页面数获取页面对象，下行强制类型转换
        //判断是否获取成功
        if (abstruct == nullptr){
            qDebug() << "Index" << i << "connect Failed";
        }else {
            connect(abstruct, &AbstructClass::signalJumpWidget, this, &MainWindow::slotJumpWidget);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//槽函数实现
void MainWindow::slotJumpWidget(int index)
{
    //在跳转相应界面的时候调用各自界面的函数
    switch (index)
    {
    case JumpType::LOG:
    {
        ui->Log->resetWidget();
        break;
    }
    case JumpType::REG:
    {
        ui->Reg->resetWidget();
        break;
    }
    case JumpType::INFOR:
    {
        break;
    }
    case JumpType::ATDA:
    {
        break;
    }
    case JumpType::SEL:
    {
        break;
    }
    case JumpType::IM:
    {
        break;
    }
    case JumpType::DEL:
    {
        break;
    }
    case JumpType::MOD:
    {
        break;
    }
    default:
    {
        break;
    }
    }
    ui->stackedWidget->setCurrentIndex(index);
}

