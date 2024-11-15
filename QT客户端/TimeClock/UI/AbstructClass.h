#ifndef ABSTRUCTCLASS_H
#define ABSTRUCTCLASS_H

#include <QWidget>
#include <Config.hpp>
#include "AccountAndInfoDB.h"
#include <QMessageBox>

//界面抽象类
class AbstructClass : public QWidget
{
    Q_OBJECT
public:
    explicit AbstructClass(QWidget *parent = nullptr);
    //下行强制类型转换需要的纯虚函数--->将析构函数设置为纯虚函数
    virtual ~AbstructClass();


    virtual void resetWidget() = 0;//清除纯虚函数，每个派生类都要实现

signals:
    void signalJumpWidget(int index);

public slots:
};

#endif // ABSTRUCTCLASS_H
