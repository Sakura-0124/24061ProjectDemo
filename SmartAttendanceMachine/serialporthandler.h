#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <QObject>
#include <QSerialPort>

class SerialPortHandler : public QObject {
    Q_OBJECT

public:
    explicit SerialPortHandler(QObject *parent = nullptr);
    ~SerialPortHandler();

    void openPort(const QString &portName);
    void closePort();
    void sendData(const QByteArray &data);

private slots:
    void readData();

private:
    QSerialPort *serial;
};

#endif // SERIALPORTHANDLER_H
