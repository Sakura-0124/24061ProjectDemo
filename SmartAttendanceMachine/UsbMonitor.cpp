#include "UsbMonitor.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

UsbMonitor::UsbMonitor(QObject *parent) : QObject(parent)
{
    m_process = new QProcess(this);
}

void UsbMonitor::startMonitoring()
{
    m_process->start("udevadm", QStringList() << "monitor" << "-u");
    connect(m_process, &QProcess::readyReadStandardOutput, this, &UsbMonitor::handleUsbEvent);
}

void UsbMonitor::handleUsbEvent()
{
    QString output = m_process->readAllStandardOutput();
    if (output.contains("add")) {
        // 检测到U盘插入，执行导出逻辑
        exportAttendanceDataToUsb();
    }
}

void UsbMonitor::exportAttendanceDataToUsb()
{
    QString usbPath = "/media/usb";
    QFile exportFile(usbPath + "/attendance_data.csv");
    if (exportFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&exportFile);
        // 写入考勤数据到csv文件
        out << "EmployeeID,Date,Time\n";
        out << "1001,2024-11-20,09:00\n";  // 示例考勤数据
        exportFile.close();
    } else {
        qDebug() << "无法打开文件进行写入";
    }
}
