/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableView *excellentEmployeesTableView;
    QTableView *signInTableView;
    QLabel *fingerprintStatusLabel;
    QPushButton *fingerprintButton;
    QPushButton *exportButton;
    QLineEdit *portNameEdit;
    QPushButton *openButton;
    QPushButton *sendButton;
    QPushButton *closeButton;
    QLineEdit *dataEdit;
    QTextBrowser *textBrowser;
    QPushButton *voiceRecognitionButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(630, 512);
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(225, 240, 255, 255), stop:0.497512 rgba(221, 243, 228, 255), stop:1 rgba(255, 229, 230, 255));\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        excellentEmployeesTableView = new QTableView(centralwidget);
        excellentEmployeesTableView->setObjectName(QString::fromUtf8("excellentEmployeesTableView"));
        excellentEmployeesTableView->setGeometry(QRect(0, 10, 260, 170));
        excellentEmployeesTableView->setStyleSheet(QString::fromUtf8("#excellentEmployeesTableView\n"
"{\n"
"	border-radius:12px;\n"
"	background-color: rgba(255, 255, 255,125);\n"
"}"));
        signInTableView = new QTableView(centralwidget);
        signInTableView->setObjectName(QString::fromUtf8("signInTableView"));
        signInTableView->setGeometry(QRect(270, 10, 350, 220));
        signInTableView->setStyleSheet(QString::fromUtf8("#signInTableView\n"
"{\n"
"	border-radius:12px;\n"
"	background-color: rgba(255, 255, 255,125);\n"
"}"));
        fingerprintStatusLabel = new QLabel(centralwidget);
        fingerprintStatusLabel->setObjectName(QString::fromUtf8("fingerprintStatusLabel"));
        fingerprintStatusLabel->setGeometry(QRect(0, 190, 260, 45));
        fingerprintStatusLabel->setStyleSheet(QString::fromUtf8("#fingerprintStatusLabel\n"
"{\n"
"	border-radius:12px;\n"
"	color: rgb(88, 71, 175);\n"
"	background-color: rgba(237, 233, 254,125);\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"}"));
        fingerprintStatusLabel->setAlignment(Qt::AlignCenter);
        fingerprintButton = new QPushButton(centralwidget);
        fingerprintButton->setObjectName(QString::fromUtf8("fingerprintButton"));
        fingerprintButton->setGeometry(QRect(0, 250, 260, 80));
        fingerprintButton->setStyleSheet(QString::fromUtf8("#fingerprintButton\n"
"{\n"
"	border-radius:12px;\n"
"	color: rgb(19, 123, 149);\n"
"	background-color: rgba(216, 243, 246,125);\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"}"));
        exportButton = new QPushButton(centralwidget);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setGeometry(QRect(270, 250, 350, 80));
        exportButton->setStyleSheet(QString::fromUtf8("#exportButton\n"
"{\n"
"	border-radius:12px;\n"
"	color: rgb(0, 145, 254);\n"
"	background-color: rgba(225, 240, 255,125);\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"}"));
        portNameEdit = new QLineEdit(centralwidget);
        portNameEdit->setObjectName(QString::fromUtf8("portNameEdit"));
        portNameEdit->setGeometry(QRect(0, 340, 151, 71));
        portNameEdit->setStyleSheet(QString::fromUtf8("#portNameEdit\n"
"{\n"
"	border-radius:12px;\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"	background-color: rgba(255, 255, 255,125);\n"
"}"));
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(330, 340, 93, 71));
        openButton->setStyleSheet(QString::fromUtf8("#openButton\n"
"{\n"
"	border-radius:12px;\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"	color: rgb(22, 121, 77);\n"
"	background-color: rgba(221, 243, 228,125);\n"
"}"));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(530, 340, 93, 71));
        sendButton->setStyleSheet(QString::fromUtf8("#sendButton\n"
"{\n"
"	border-radius:12px;\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"	color: rgb(0, 145, 254);\n"
"	background-color: rgba(225, 240, 255,125);\n"
"}"));
        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(430, 340, 93, 71));
        closeButton->setStyleSheet(QString::fromUtf8("#closeButton\n"
"{\n"
"	border-radius:12px;\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"	color: rgb(206, 42, 49);\n"
"	background-color: rgba(255, 229, 230,125);\n"
"}"));
        dataEdit = new QLineEdit(centralwidget);
        dataEdit->setObjectName(QString::fromUtf8("dataEdit"));
        dataEdit->setGeometry(QRect(160, 340, 161, 71));
        dataEdit->setStyleSheet(QString::fromUtf8("#dataEdit\n"
"{\n"
"	border-radius:12px;\n"
"	font: 57 15pt \"\350\213\271\346\226\271UI-\346\270\257\";\n"
"	background-color: rgba(255, 255, 255,125);\n"
"}"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(0, 420, 261, 61));
        voiceRecognitionButton = new QPushButton(centralwidget);
        voiceRecognitionButton->setObjectName(QString::fromUtf8("voiceRecognitionButton"));
        voiceRecognitionButton->setGeometry(QRect(270, 420, 171, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 630, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        fingerprintStatusLabel->setText(QString());
        fingerprintButton->setText(QCoreApplication::translate("MainWindow", "\345\275\225\345\205\245\346\214\207\347\272\271", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\344\270\272Excel", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        closeButton->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        voiceRecognitionButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
