#ifndef EMPLOYEEATTENDANCEQUERYDIALOG_H
#define EMPLOYEEATTENDANCEQUERYDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class EmployeeAttendanceQueryDialog;
}

class EmployeeAttendanceQueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeAttendanceQueryDialog(QWidget *parent = nullptr);
    ~EmployeeAttendanceQueryDialog();

private slots:
    void on_queryButton_clicked();

private:
    Ui::EmployeeAttendanceQueryDialog *ui;
    void queryAttendanceRecord(const QString &employeeID, const QString &date);
};

#endif // EMPLOYEEATTENDANCEQUERYDIALOG_H
