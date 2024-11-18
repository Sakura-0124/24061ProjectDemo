#include "serialporthandler.h"
#include <QDebug>

SerialPortHandler::SerialPortHandler(QObject *parent) : QObject(parent), serial(new QSerialPort(this)) {
    // 设置串口参数
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // 连接信号和槽
    connect(serial, &QSerialPort::readyRead, this, &SerialPortHandler::readData);
}

SerialPortHandler::~SerialPortHandler() {
    if (serial->isOpen()) {
        serial->close();
    }
}

void SerialPortHandler::openPort(const QString &portName) {
    serial->setPortName(portName);
    if (!serial->open(QIODevice::ReadWrite)) {
        qDebug() << "无法打开串口" << portName << ":" << serial->errorString();
    } else {
        qDebug() << "串口" << portName << "已成功打开。";
    }
}

void SerialPortHandler::closePort() {
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "串口已关闭。";
    }
}

void SerialPortHandler::sendData(const QByteArray &data) {
    if (serial->isOpen()) {
        serial->write(data);
    } else {
        qDebug() << "串口未打开，无法发送数据！";
    }
}

void SerialPortHandler::readData() {
    if (serial->isOpen()) {
        QByteArray data = serial->readAll();
        qDebug() << "接收到的数据:" << data;
        // 在此处处理接收到的数据
    }
}
