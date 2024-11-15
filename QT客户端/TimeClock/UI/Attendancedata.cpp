#include "Attendancedata.h"
#include "ui_Attendancedata.h"

Attendancedata::Attendancedata(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::Attendancedata)
{
    ui->setupUi(this);
}

Attendancedata::~Attendancedata()
{
    delete ui;
}

void Attendancedata::resetWidget()
{

}

//回退
void Attendancedata::on_pushButton_back_clicked()
{
    emit signalJumpWidget(JumpType::SEL);
}
