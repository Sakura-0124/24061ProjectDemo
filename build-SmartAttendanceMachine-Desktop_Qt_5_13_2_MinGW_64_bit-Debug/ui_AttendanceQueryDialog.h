/********************************************************************************
** Form generated from reading UI file 'AttendanceQueryDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTENDANCEQUERYDIALOG_H
#define UI_ATTENDANCEQUERYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *queryButton;
    QDateEdit *dateEdit;
    QLineEdit *employeeIDLineEdit;
    QTextBrowser *resultTextBrowser;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(618, 534);
        queryButton = new QPushButton(Form);
        queryButton->setObjectName(QString::fromUtf8("queryButton"));
        queryButton->setGeometry(QRect(10, 20, 93, 28));
        dateEdit = new QDateEdit(Form);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(10, 80, 110, 22));
        employeeIDLineEdit = new QLineEdit(Form);
        employeeIDLineEdit->setObjectName(QString::fromUtf8("employeeIDLineEdit"));
        employeeIDLineEdit->setGeometry(QRect(140, 20, 113, 21));
        resultTextBrowser = new QTextBrowser(Form);
        resultTextBrowser->setObjectName(QString::fromUtf8("resultTextBrowser"));
        resultTextBrowser->setGeometry(QRect(190, 110, 256, 192));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        queryButton->setText(QCoreApplication::translate("Form", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTENDANCEQUERYDIALOG_H
