#ifndef USBMONITOR_H
#define USBMONITOR_H

#include <QObject>
#include <QProcess>

class UsbMonitor : public QObject
{
    Q_OBJECT
public:
    explicit UsbMonitor(QObject *parent = nullptr);
    void startMonitoring();

private slots:
    void handleUsbEvent();

private:
    QProcess *m_process;
    void exportAttendanceDataToUsb();
};

#endif // USBMONITOR_H
