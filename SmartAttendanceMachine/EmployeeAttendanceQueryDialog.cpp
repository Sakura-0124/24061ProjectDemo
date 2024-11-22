#include "EmployeeAttendanceQueryDialog.h"
#include "ui_EmployeeAttendanceQueryDialog.h"
#include <QDebug>

EmployeeAttendanceQueryDialog::EmployeeAttendanceQueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeAttendanceQueryDialog)
{
    ui->setupUi(this);
    connect(ui->queryButton, &QPushButton::clicked, this, &EmployeeAttendanceQueryDialog::on_queryButton_clicked);
}

EmployeeAttendanceQueryDialog::~EmployeeAttendanceQueryDialog()
{
    delete ui;
}

void EmployeeAttendanceQueryDialog::on_queryButton_clicked()
{
    QString employeeID = ui->employeeIDLineEdit->text();
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    queryAttendanceRecord(employeeID, date);
}

void EmployeeAttendanceQueryDialog::queryAttendanceRecord(const QString &employeeID, const QString &date)
{
    QSqlQuery query;
    QString queryString = QString("SELECT * FROM attendance WHERE employee_id = '%1' AND date = '%2'")
                          .arg(employeeID).arg(date);
    if (query.exec(queryString)) {
        QString result;
        while (query.next()) {
            QString time = query.value("time").toString();
            result += QString("员工ID: %1, 日期: %2, 时间: %3\n").arg(employeeID).arg(date).arg(time);
        }
        if (result.isEmpty()) {
            result = "没有找到相关记录。";
        }
        ui->resultTextBrowser->setText(result);
    } else {
        qDebug() << "查询失败：" << query.lastError();
        ui->resultTextBrowser->setText("查询失败，请检查输入。");
    }
}
