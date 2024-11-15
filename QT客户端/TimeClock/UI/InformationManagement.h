#ifndef INFORMATIONMANAGEMENT_H
#define INFORMATIONMANAGEMENT_H

#include "AbstructClass.h"

namespace Ui {
class InformationManagement;
}

class InformationManagement : public AbstructClass
{
    Q_OBJECT

public:
    explicit InformationManagement(QWidget *parent = nullptr);
    ~InformationManagement() override;
    virtual void resetWidget() override;

private slots:
    //回退
    void on_pushButton_back_clicked();

private:
    Ui::InformationManagement *ui;
};

#endif // INFORMATIONMANAGEMENT_H
