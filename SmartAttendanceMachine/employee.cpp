#include "employee.h"

// Employee 构造函数实现
Employee::Employee(int id, const QString &name, const QString &performance)
    : m_id(id), m_name(name), m_performance(performance)
{
}

// 获取员工ID
int Employee::id() const
{
    return m_id;
}

// 获取员工姓名
QString Employee::name() const
{
    return m_name;
}

// 获取员工表现
QString Employee::performance() const
{
    return m_performance;
}
