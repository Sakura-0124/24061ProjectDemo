#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee
{
public:
    // 构造函数声明
    Employee(int id, const QString &name, const QString &performance);

    // 成员函数声明
    int id() const;
    QString name() const;
    QString performance() const;

private:
    int m_id;
    QString m_name;
    QString m_performance;
};

#endif // EMPLOYEE_H
