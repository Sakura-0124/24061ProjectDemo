#include "mainwindow.h"
#include "UsbMonitor.h"
#include <QApplication>
#include "EmployeeAttendanceQueryDialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UsbMonitor usbMonitor;
    usbMonitor.startMonitoring();
    MainWindow w;
    w.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("attendance.db");
        if (!db.open()) {
            qDebug() << "无法连接到数据库：" << db.lastError().text();
            return -1;
        }

     EmployeeAttendanceQueryDialog dialog;

    return a.exec();
}
