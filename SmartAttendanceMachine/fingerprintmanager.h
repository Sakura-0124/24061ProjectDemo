#ifndef FINGERPRINTMANAGER_H
#define FINGERPRINTMANAGER_H

#include <QObject>

class FingerprintManager : public QObject
{
    Q_OBJECT

public:
    explicit FingerprintManager(QObject *parent = nullptr);
    void startEnrollment();

private:
    void connectToDevice();  // 连接指纹设备

signals:
    void enrollmentFinished(bool success);
};

#endif // FINGERPRINTMANAGER_H
