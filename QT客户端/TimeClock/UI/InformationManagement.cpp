#include "InformationManagement.h"
#include "ui_InformationManagement.h"

InformationManagement::InformationManagement(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::InformationManagement)
{
    ui->setupUi(this);
}

InformationManagement::~InformationManagement()
{
    delete ui;
}

void InformationManagement::resetWidget()
{

}
//回退
void InformationManagement::on_pushButton_back_clicked()
{
    emit signalJumpWidget(JumpType::SEL);
}
