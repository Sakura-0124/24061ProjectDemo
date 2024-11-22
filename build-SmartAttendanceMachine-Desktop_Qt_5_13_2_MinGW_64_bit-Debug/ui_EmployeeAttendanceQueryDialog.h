/********************************************************************************
** Form generated from reading UI file 'EmployeeAttendanceQueryDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEATTENDANCEQUERYDIALOG_H
#define UI_EMPLOYEEATTENDANCEQUERYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *employeeIDLineEdit;
    QDateEdit *dateEdit;
    QTextBrowser *resultTextBrowser;
    QPushButton *queryButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(403, 304);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        employeeIDLineEdit = new QLineEdit(Dialog);
        employeeIDLineEdit->setObjectName(QString::fromUtf8("employeeIDLineEdit"));
        employeeIDLineEdit->setGeometry(QRect(20, 20, 113, 21));
        dateEdit = new QDateEdit(Dialog);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(20, 60, 110, 22));
        resultTextBrowser = new QTextBrowser(Dialog);
        resultTextBrowser->setObjectName(QString::fromUtf8("resultTextBrowser"));
        resultTextBrowser->setGeometry(QRect(20, 90, 261, 141));
        queryButton = new QPushButton(Dialog);
        queryButton->setObjectName(QString::fromUtf8("queryButton"));
        queryButton->setGeometry(QRect(190, 20, 93, 28));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        queryButton->setText(QCoreApplication::translate("Dialog", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEATTENDANCEQUERYDIALOG_H
