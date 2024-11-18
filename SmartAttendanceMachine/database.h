#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include <QDateTime>

struct Attendance {
    int employeeId;
    QString employeeName;
    QDateTime signInTime;
};

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    bool exportToExcel();
    QList<Attendance> getAttendanceList();

private:
    QSqlDatabase db;
    bool connectToDatabase();
};

#endif // DATABASE_H
