#ifndef REGISTER_H
#define REGISTER_H

#include "AbstructClass.h"

namespace Ui {
class Register;
}

class Register : public AbstructClass
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register() override;

    //清除界面资源
    virtual void resetWidget() override;

private slots:
    void on_pushButton_clicked();
    //回退
    void on_pushButton_back_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
