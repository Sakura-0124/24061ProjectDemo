#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "fingerprintmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateSignInInfo();
    void exportAttendanceData();
    void enrollFingerprint();

private:
    Ui::MainWindow *ui;
    Database *database;                // 数据库对象
    FingerprintManager *fingerprint;   // 指纹管理对象
};
#endif // MAINWINDOW_H
