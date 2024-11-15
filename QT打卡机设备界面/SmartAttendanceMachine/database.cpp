#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QAxObject>
#include <QDebug>
#include <QDir>

Database::Database(QObject *parent) : QObject(parent)
{
    connectToDatabase();
}

bool Database::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("attendance.db");
    if (!db.open()) {
        qDebug() << "无法连接到数据库：" << db.lastError().text();
        return false;
    }
    return true;
}

QList<Attendance> Database::getAttendanceList()
{
    QList<Attendance> attendanceList;
    QSqlQuery query("SELECT employee_id, employee_name, sign_in_time FROM attendance");

    while (query.next()) {
        Attendance att;
        att.employeeId = query.value(0).toInt();
        att.employeeName = query.value(1).toString();
        att.signInTime = query.value(2).toDateTime();
        attendanceList.append(att);
    }

    return attendanceList;
}

bool Database::exportToExcel()
{
    QAxObject *excel = new QAxObject("Excel.Application");
    if (!excel) {
        qDebug() << "无法创建Excel对象";
        return false;
    }

    excel->dynamicCall("SetVisible(bool Visible)", false);
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel->querySubObject("ActiveWorkbook");
    QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

    // 填充Excel内容
    worksheet->querySubObject("Cells(int,int)", 1, 1)->setProperty("Value", "员工ID");
    worksheet->querySubObject("Cells(int,int)", 1, 2)->setProperty("Value", "姓名");
    worksheet->querySubObject("Cells(int,int)", 1, 3)->setProperty("Value", "签到时间");

    QList<Attendance> attendanceList = getAttendanceList();
    for (int i = 0; i < attendanceList.size(); ++i) {
        worksheet->querySubObject("Cells(int,int)", i + 2, 1)->setProperty("Value", attendanceList[i].employeeId);
        worksheet->querySubObject("Cells(int,int)", i + 2, 2)->setProperty("Value", attendanceList[i].employeeName);
        worksheet->querySubObject("Cells(int,int)", i + 2, 3)->setProperty("Value", attendanceList[i].signInTime.toString());
    }

    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators("考勤数据.xlsx"));
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    delete excel;

    return true;
}
