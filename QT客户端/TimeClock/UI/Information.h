#ifndef INFORMATION_H
#define INFORMATION_H

#include "AbstructClass.h"

namespace Ui {
class Information;
}

class Information : public AbstructClass
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = nullptr);
    ~Information() override;
    virtual void resetWidget() override;

private slots:
    //回退
    void on_pushButton_back_clicked();
    //保存信息
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
