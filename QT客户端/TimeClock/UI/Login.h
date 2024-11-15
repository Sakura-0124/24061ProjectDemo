#ifndef LOGIN_H
#define LOGIN_H

#include "AbstructClass.h"
#include <QMovie>
#include <QDebug>

namespace Ui {
class Login;
}

class Login : public AbstructClass
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;
    virtual void resetWidget() override;


private slots:
    //登录槽
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
