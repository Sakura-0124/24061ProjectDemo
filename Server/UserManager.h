#ifndef USER_MANAGER_H
#define USER_MANAGER_H


#include "General.h"
#include "JsonHandler.h"

class UserManager {
public:
    static UserManager& getInstance();

    // 管理员账号管理
    std::string adminRegister(const Json::Value& request);
    std::string adminLogin(const Json::Value& request);
    bool isAdminLoggedIn();  // 修改这里，移除参数
    void adminLogout();      // 修改这里，移除参数

    // 客户端用户管理
    std::string handleLogin(const Json::Value& request);
    std::string handleRegister(const Json::Value& request);

private:
    UserManager();
    ~UserManager();
    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;

    void loadAdminAccounts();
    void saveAdminAccounts();

    std::unordered_map<std::string, std::string> admin_accounts;  // 管理员账号
    bool admin_logged_in;  // 添加登录状态标志
    std::mutex admin_mutex;

    const std::string ADMIN_FILE = "admin_accounts.json";
};

#endif