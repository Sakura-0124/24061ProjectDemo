#ifndef MODIFYACCOUNT_H
#define MODIFYACCOUNT_H

#include "AbstructClass.h"

namespace Ui {
class ModifyAccount;
}

class ModifyAccount : public AbstructClass
{
    Q_OBJECT

public:
    explicit ModifyAccount(QWidget *parent = nullptr);
    ~ModifyAccount() override;
    virtual void resetWidget() override;

private slots:
    //更改密码转到槽
    void on_pushButton_mod_clicked();
    //注销账号转到槽
    void on_pushButton_del_clicked();
    //回退
    void on_pushButton_back_clicked();

private:
    Ui::ModifyAccount *ui;
};

#endif // MODIFYACCOUNT_H
