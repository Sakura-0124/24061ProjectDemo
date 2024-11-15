#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    //更改窗口名字
    w.setWindowTitle("智能打卡机");
    w.show();
    return a.exec();
}
