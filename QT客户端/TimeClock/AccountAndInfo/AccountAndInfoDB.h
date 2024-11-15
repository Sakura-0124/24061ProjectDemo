#ifndef ACCOUNTANDINFODB_H
#define ACCOUNTANDINFODB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

//单例模式
class AccountAndInfoDB : public QObject
{
    Q_OBJECT
public:
    //获取静态对象
    static AccountAndInfoDB *getInstance();
    //销毁
    static void ReleaseADInstance();

    class AutoReleaseAD//类中类，静态变量对象释放时，调用析构函数
    {
    public:
        AutoReleaseAD() = default;
        ~AutoReleaseAD();
    };

    //数据库操作
    bool CreateDB();//创建数据库
    bool CreatAccountTable();//建Account表
    bool InsertAccount(QString id, QString account, QString password);//插入账号数据
    bool ModAccount(QString id, QString newpassword);//更改密码
    bool DelAccount(QString id);//删除账号

    bool CreatInfoTable();//建员工信息表
    bool InsertInfo(QString id, QString name, QString age,QString sex, QString dep);//插入员工信息
    bool ModInfo();//更改员工信息
    bool DelInfo();//删除员工

signals:
public slots:

private:
    explicit AccountAndInfoDB(QObject *parent = nullptr);//将构造函数放到private里
    static AccountAndInfoDB *AD;//数据库静态成员
    static pthread_mutex_t lock;//静态锁
    static AutoReleaseAD AR;//
    QSqlDatabase database;//数据库对象
};

#endif // ACCOUNTANDINFODB_H
