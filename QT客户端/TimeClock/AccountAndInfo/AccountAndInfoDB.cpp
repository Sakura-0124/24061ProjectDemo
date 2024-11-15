#include "AccountAndInfoDB.h"

AccountAndInfoDB * AccountAndInfoDB::AD = nullptr;
pthread_mutex_t AccountAndInfoDB::lock = PTHREAD_MUTEX_INITIALIZER;
AccountAndInfoDB::AutoReleaseAD AccountAndInfoDB::AR;

//获取操作数据库的对象
AccountAndInfoDB *AccountAndInfoDB::getInstance()
{
    if (!AD)
    {
        pthread_mutex_lock(&lock);//懒汉式上锁线程安全
        if (!AD)
        {
            AD = new AccountAndInfoDB;//创建对象
        }
        pthread_mutex_unlock(&lock);
    }
    return AD;
}

//释放资源
void AccountAndInfoDB::ReleaseADInstance()
{
    if (AD != nullptr)
    {
        delete AD;
        AD = nullptr;
    }
}

//创建打开数据库
bool AccountAndInfoDB::CreateDB()
{
    //检查连接名是否存在，存在，返回对应连接，不存在，手动创建一个，不允许创建同名的多个连接
    if (QSqlDatabase::contains("default_connection")) {
        database = QSqlDatabase::database("default_connection");
        qDebug() << "Exist Connection";
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE");//数据库驱动
        database.setDatabaseName("user.db");//设置数据库路径，对应的文件名不存在就创建
        qDebug() << "Not Exist Connection";
    }
    qDebug() << "Create Database Success";
    database.open();//开启数据库，并且检查数据库是否打开
    if (!database.open()) {
        qDebug() << "Error Open" << database.lastError();
    } else {
        qDebug() << "Success Open";
    }
    return true;
}

// 建表
bool AccountAndInfoDB::CreatAccountTable()
{
    QSqlQuery dt(database);//创建对象
    database.transaction();//开启事务
    //prepare函数定义需要去执行的语句，exec函数去执行
    dt.prepare("create table if not exists Login(id int primary key, account int, password char)");
    if (!dt.exec()) {
        qDebug() << "Error AccountTable Exec" << dt.lastError();
        database.rollback();//执行失败后通过rollback函数进行回退
    } else {
        qDebug() << "Create AccountTable Success";
        database.commit();//正确，使用commit函数进行提交
    }
    return true;
}

// 插入
bool AccountAndInfoDB::InsertAccount(QString id, QString account, QString password)
{
    QSqlQuery dt(database);
    database.transaction();
    //占位符的方法，一一绑定
    dt.prepare("INSERT INTO Login(id, account, password) values (:cid, :caccount, :cpassword)");
    dt.bindValue(":cid", id);
    dt.bindValue(":caccount", account);
    dt.bindValue(":cpassword", password);

    if (!dt.exec()) {
        qDebug() << "Error AcountInto Exec" << dt.lastError();
        database.rollback();//执行失败后通过rollback函数进行回退
    } else {
        qDebug() << "INSERT Acount Success";
        database.commit();//正确，使用commit函数进行提交
    }
    return true;
}

//密码更改
bool AccountAndInfoDB::ModAccount(QString id, QString newpassword)
{
    QSqlQuery dt(database);
    database.transaction();
    //占位符的方法，一一绑定
    dt.prepare(QString("UPDATE Login SET password = :cnewpassword WHERE id = :cid;"));
    dt.bindValue(":cid", id);
    dt.bindValue(":cnewpassword", newpassword);

    if (!dt.exec()) {
        qDebug() << "Error AccountSet Exec" << dt.lastError();
        database.rollback();//执行失败后通过rollback函数进行回退
    } else {
        qDebug() << "Mod AccountSet Success";
        database.commit();//正确，使用commit函数进行提交
    }
    return true;
}

//删除管理员
bool AccountAndInfoDB::DelAccount(QString id)
{
    QSqlQuery dt(database);
    database.transaction();
    //占位符的方法，一一绑定
    dt.prepare(QString("DELETE FROM Login WHERE id = :cid;"));
    dt.bindValue(":cid", id);

    if (!dt.exec()) {
        qDebug() << "Error AccountDel Exec" << dt.lastError();
        database.rollback();//执行失败后通过rollback函数进行回退
    } else {
        qDebug() << "Del AccountDel Success";
        database.commit();//正确，使用commit函数进行提交
    }
    return true;
}

bool AccountAndInfoDB::CreatInfoTable()
{
    QSqlQuery dt(database);//创建对象
    database.transaction();//开启事务
    //prepare函数定义需要去执行的语句，exec函数去执行
    dt.prepare("create table if not exists Info(id INTEGER primary key, name TEXT, age INTEGER, sex TEXT, dep TEXT)");
    if (!dt.exec()) {
        qDebug() << "Error InfoTable Exec" << dt.lastError();
        database.rollback();//执行失败后通过rollback函数进行回退
    } else {
        qDebug() << "Create InfoTable Success";
        database.commit();//正确，使用commit函数进行提交
    }
    return true;
}

bool AccountAndInfoDB::InsertInfo(QString id, QString name, QString age, QString sex, QString dep)
{
    QSqlQuery dt(database);
    database.transaction();
    //占位符的方法，一一绑定
    dt.prepare("INSERT INTO Info(id, name, age, sex, dep) values (:cid, :cname, :cage, :csex, :cdep)");
    dt.bindValue(":cid", id);
    dt.bindValue(":cname", name);
    dt.bindValue(":cage", age);
    dt.bindValue(":csex", sex);
    dt.bindValue(":cdep", dep);

    if (!dt.exec()) {
        qDebug() << "Error InfoInto Exec" << dt.lastError();
        database.rollback();//执行失败后通过rollback函数进行回退
    } else {
        qDebug() << "INSERT InfoINTO Success";
        database.commit();//正确，使用commit函数进行提交
    }
    return true;
}

//构造函数
AccountAndInfoDB::AccountAndInfoDB(QObject *parent) : QObject(parent)
{
    CreateDB();//构造函数调用数据库开启函数
}

//析构函数
AccountAndInfoDB::AutoReleaseAD::~AutoReleaseAD()
{
    ReleaseADInstance();
}
