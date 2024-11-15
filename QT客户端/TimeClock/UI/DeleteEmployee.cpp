#include "DeleteEmployee.h"
#include "ui_DeleteEmployee.h"

DeleteEmployee::DeleteEmployee(QWidget *parent) :
    AbstructClass(parent),
    ui(new Ui::DeleteEmployee)
{
    ui->setupUi(this);
}

DeleteEmployee::~DeleteEmployee()
{
    delete ui;
}

void DeleteEmployee::resetWidget()
{

}
//回退
void DeleteEmployee::on_pushButton_back_clicked()
{
    emit signalJumpWidget(JumpType::SEL);
}
