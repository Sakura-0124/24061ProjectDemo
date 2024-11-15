#ifndef SELECT_H
#define SELECT_H

#include "AbstructClass.h"

namespace Ui {
class Select;
}

class Select : public AbstructClass
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = nullptr);
    ~Select() override;
    virtual void resetWidget() override;

    //初始化ToolButton控件，设置
    void initToolButton();

private slots:
    //信息录入转到槽
    void on_toolButton_Infor_clicked();
    //考勤数据转到槽
    void on_toolButton_AtDa_clicked();
    //信息管理转到槽
    void on_toolButton_IM_clicked();
    //员工删除转到槽
    void on_toolButton_Del_clicked();
    //账户更改转到槽
    void on_toolButton_Mod_clicked();
    //回退
    void on_pushButton_back_clicked();

private:
    Ui::Select *ui;
};

#endif // SELECT_H
