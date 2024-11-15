#include "UserManager.h"

UserManager& UserManager::getInstance() {
    static UserManager instance;
    return instance;
}

UserManager::UserManager() :admin_logged_in(false){
    loadAdminAccounts();
}

UserManager::~UserManager() {
    saveAdminAccounts();
}

void UserManager::loadAdminAccounts() {
    std::ifstream file(ADMIN_FILE);
    if (file.is_open()) {
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(file, root)) {
            for (const auto& username : root.getMemberNames()) {
                admin_accounts[username] = root[username].asString();
            }
        }
        file.close();
    }
}

void UserManager::saveAdminAccounts() {
    Json::Value root;
    for (const auto& pair : admin_accounts) {
        root[pair.first] = pair.second;
    }

    std::ofstream file(ADMIN_FILE);
    if (file.is_open()) {
        Json::StyledWriter writer;
        file << writer.write(root);
        file.close();
    }
}

std::string UserManager::adminRegister(const Json::Value& request) {
    Json::Value response;
    
    if (!request.isMember("username") || !request.isMember("password")) {
        response["status"] = "error";
        response["message"] = "缺少用户名或密码";
        return Json::FastWriter().write(response);
    }

    std::string username = request["username"].asString();
    std::string password = request["password"].asString();

    std::lock_guard<std::mutex> lock(admin_mutex);
    
    if (admin_accounts.find(username) != admin_accounts.end()) {
        response["status"] = "error";
        response["message"] = "管理员账号已存在";
    } else {
        admin_accounts[username] = password;
        saveAdminAccounts();
        response["status"] = "success";
        response["message"] = "管理员账号注册成功";
    }

    return Json::FastWriter().write(response);
}

std::string UserManager::adminLogin(const Json::Value& request) {
    Json::Value response;
    
    if (!request.isMember("username") || !request.isMember("password")) {
        response["status"] = "error";
        response["message"] = "缺少用户名或密码";
        return Json::FastWriter().write(response);
    }

    std::string username = request["username"].asString();
    std::string password = request["password"].asString();

    std::lock_guard<std::mutex> lock(admin_mutex);
    
    auto it = admin_accounts.find(username);
    if (it != admin_accounts.end() && it->second == password) {
        admin_logged_in = true;  // 设置登录状态
        response["status"] = "success";
        response["message"] = "管理员登录成功";
        std::cout << "管理员 " << username << " 登录成功" << std::endl;
    } else {
        response["status"] = "error";
        response["message"] = "管理员账号或密码错误";
    }

    return Json::FastWriter().write(response);
}

bool UserManager::isAdminLoggedIn() {
    std::lock_guard<std::mutex> lock(admin_mutex);
    return admin_logged_in;
}

void UserManager::adminLogout() {
    std::lock_guard<std::mutex> lock(admin_mutex);
    admin_logged_in = false;
    std::cout << "管理员已登出" << std::endl;
}

std::string UserManager::handleLogin(const Json::Value& request) {
    Json::Value response;
    response["status"] = "error";
    response["message"] = "普通用户登录功能未实现";
    return Json::FastWriter().write(response);
}

std::string UserManager::handleRegister(const Json::Value& request) {
    Json::Value response;
    response["status"] = "error";
    response["message"] = "普通用户注册功能未实现";
    return Json::FastWriter().write(response);
}