#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include "database.h"
#include "fingerprintmanager.h"
#include "serialporthandler.h"

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
    void onOpenButtonClicked();
    void onCloseButtonClicked();
    void onSendButtonClicked();
    void on_voiceRecognitionButton_clicked();  // 按钮点击事件槽函数

private:
    Ui::MainWindow *ui;
    void handleVoiceCommand(const QString &command);  // 处理语音命令
    Database *database;                // 数据库对象
    FingerprintManager *fingerprint;   // 指纹管理对象
    SerialPortHandler *serialHandler;  // 声明 serialHandler 作为成员变量
};
#endif // MAINWINDOW_H
