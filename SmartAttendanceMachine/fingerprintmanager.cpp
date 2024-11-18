#include "fingerprintmanager.h"
#include <QDebug>

FingerprintManager::FingerprintManager(QObject *parent)
    : QObject(parent)
{
    connectToDevice();
}

void FingerprintManager::connectToDevice()
{
    // 假设通过USB或串口连接到指纹设备的初始化逻辑
    qDebug() << "指纹设备已连接";
}

void FingerprintManager::startEnrollment()
{
    // 启动指纹录入的逻辑，可以加入设备交互的细节
    qDebug() << "指纹录入开始...";
    // 模拟指纹录入过程
    bool success = true; // 假设录入成功
    emit enrollmentFinished(success);
}
