#ifndef DELETEEMPLOYEE_H
#define DELETEEMPLOYEE_H

#include "AbstructClass.h"

namespace Ui {
class DeleteEmployee;
}

class DeleteEmployee : public AbstructClass
{
    Q_OBJECT

public:
    explicit DeleteEmployee(QWidget *parent = nullptr);
    ~DeleteEmployee() override;
    virtual void resetWidget() override;

private slots:
    //回退
    void on_pushButton_back_clicked();

private:
    Ui::DeleteEmployee *ui;
};

#endif // DELETEEMPLOYEE_H
