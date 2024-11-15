#ifndef ATTENDANCEDATA_H
#define ATTENDANCEDATA_H

#include "AbstructClass.h"

namespace Ui {
class Attendancedata;
}

class Attendancedata : public AbstructClass
{
    Q_OBJECT

public:
    explicit Attendancedata(QWidget *parent = nullptr);
    ~Attendancedata() override;
    virtual void resetWidget() override;

private slots:
    //回退
    void on_pushButton_back_clicked();

private:
    Ui::Attendancedata *ui;
};

#endif // ATTENDANCEDATA_H
