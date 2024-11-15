#include "EpollServer.h"

EpollServer::EpollServer(int port) : running(false), thread_pool(4) {
    // 创建服务器socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        throw std::runtime_error("创建socket失败");
    }

    // 设置socket选项
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        close(server_fd);
        throw std::runtime_error("设置socket选项失败");
    }

    // 绑定地址和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        close(server_fd);
        throw std::runtime_error("绑定端口失败");
    }

    // 监听连接
    if (listen(server_fd, SOMAXCONN) == -1) {
        close(server_fd);
        throw std::runtime_error("监听失败");
    }

    // 创建epoll实例
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        close(server_fd);
        throw std::runtime_error("创建epoll实例失败");
    }

    // 添加服务器socket到epoll
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
        close(epoll_fd);
        close(server_fd);
        throw std::runtime_error("添加服务器socket到epoll失败");
    }

    setNonBlocking(server_fd);
}

EpollServer::~EpollServer() {
    if (epoll_fd != -1) {
        close(epoll_fd);
    }
    if (server_fd != -1) {
        close(server_fd);
    }
}

void EpollServer::setNonBlocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("获取socket标志失败");
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("设置socket非阻塞失败");
    }
}

void EpollServer::run() {
    running = true;
    struct epoll_event events[MAX_EVENTS];

    while (running) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            if (errno == EINTR) {
                continue;
            }
            throw std::runtime_error("epoll_wait失败");
        }

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == server_fd) {
                handleNewConnection();
            } else {
                int current_fd = events[i].data.fd;
                thread_pool.enqueue([this, current_fd] {
                    handleClientData(current_fd);
                });
            }
        }
    }
}

void EpollServer::stop() {
    running = false;
}

void EpollServer::handleNewConnection() {
    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            }
            std::cerr << "接受连接失败" << std::endl;
            break;
        }

        setNonBlocking(client_fd);

        struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = client_fd;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
            std::cerr << "添加客户端到epoll失败" << std::endl;
            close(client_fd);
            continue;
        }

        std::cout << "新客户端连接，fd: " << client_fd << std::endl;
    }
}

std::string EpollServer::getClientInfo(int client_fd) {
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    getpeername(client_fd, (struct sockaddr*)&addr, &addr_len);
    
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
    
    return std::string(ip) + ":" + std::to_string(ntohs(addr.sin_port));
}

void EpollServer::handleAdminAction(int client_fd, const Json::Value& json_request, bool isHttp) {
    std::string action = json_request["action"].asString();
    std::string response;
    
    if (action == "admin_register") {
        response = UserManager::getInstance().adminRegister(json_request);
    }
    else if (action == "admin_login") {
        response = UserManager::getInstance().adminLogin(json_request);
    }
    else if (action == "admin_logout") {
        if (UserManager::getInstance().isAdminLoggedIn()) {
            UserManager::getInstance().adminLogout();
            Json::Value resp;
            resp["status"] = "success";
            resp["message"] = "管理员已登出";
            response = Json::FastWriter().write(resp);
        } else {
            Json::Value resp;
            resp["status"] = "error";
            resp["message"] = "未登录状态";
            response = Json::FastWriter().write(resp);
        }
    }

    if (isHttp) {
        sendResponse(client_fd, response);
    } else {
        write(client_fd, response.c_str(), response.length());
        write(client_fd, "\n", 1);
    }
}

void EpollServer::handleJsonMessage(int client_fd, const Json::Value& json_request, bool isHttp) {
    std::string client_info = getClientInfo(client_fd);
    std::string response;

    if (UserManager::getInstance().isAdminLoggedIn()) {
        std::cout << "\n================================" << std::endl;
        std::cout << "收到来自客户端[fd=" << client_fd << "] " << client_info << " 的JSON消息：" << std::endl;
        Json::StyledWriter writer;
        std::cout << writer.write(json_request) << std::endl;
        std::cout << "================================\n" << std::endl;

        Json::Value resp;
        resp["status"] = "success";
        resp["message"] = "JSON消息已收到";
        response = Json::FastWriter().write(resp);
    } else {
        Json::Value resp;
        resp["status"] = "error";
        resp["message"] = "请先以管理员身份登录";
        response = Json::FastWriter().write(resp);
    }

    if (isHttp) {
        sendResponse(client_fd, response);
    } else {
        write(client_fd, response.c_str(), response.length());
        write(client_fd, "\n", 1);
    }
}

void EpollServer::handleTextMessage(int client_fd, const std::string& message) {
    std::string client_info = getClientInfo(client_fd);
    
    if (UserManager::getInstance().isAdminLoggedIn()) {
        std::cout << "\n================================" << std::endl;
        std::cout << "收到来自客户端[fd=" << client_fd << "] " << client_info << " 的普通文本消息：" << std::endl;
        std::cout << "内容: " << message << std::endl;
        std::cout << "================================\n" << std::endl;

        std::string response = "服务器已收到普通文本消息\n";
        write(client_fd, response.c_str(), response.length());
    } else {
        std::string response = "请先以管理员身份登录\n";
        write(client_fd, response.c_str(), response.length());
    }
}

void EpollServer::handleClientData(int client_fd) {
    char buffer[BUFFER_SIZE];
    std::string data;
    
    int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            std::cout << "客户端[fd=" << client_fd << "] " << getClientInfo(client_fd) << " 断开连接" << std::endl;
        } else {
            std::cerr << "读取客户端[fd=" << client_fd << "]数据失败: " << strerror(errno) << std::endl;
        }
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
        close(client_fd);
        return;
    }

    buffer[bytes_read] = '\0';
    data = buffer;

    try {
        bool isHttp = (data.find("HTTP/1.1") != std::string::npos);
        Json::Value json_request;
        bool isJson = false;

        // 解析JSON
        if (isHttp) {
            std::string json_str = json_handler.extractJsonFromHTTP(data);
            if (!json_str.empty()) {
                isJson = json_handler.parseJson(json_str, json_request);
            }
        } else {
            Json::Reader reader;
            isJson = (data[0] == '{' && reader.parse(data, json_request));
        }

        if (isJson) {
            if (json_request.isMember("action")) {
                handleAdminAction(client_fd, json_request, isHttp);
            } else {
                handleJsonMessage(client_fd, json_request, isHttp);
            }
        } else if (!isHttp) {
            handleTextMessage(client_fd, data);
        }
    } catch (const std::exception& e) {
        std::cerr << "处理客户端[fd=" << client_fd << "]消息时发生错误: " << e.what() << std::endl;
        std::string error_response = "处理消息时发生错误\n";
        write(client_fd, error_response.c_str(), error_response.length());
    }
}

std::string EpollServer::buildHttpResponse(const std::string& content) {
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: application/json\r\n";
    response += "Content-Length: " + std::to_string(content.length()) + "\r\n";
    response += "Connection: close\r\n";
    response += "Access-Control-Allow-Origin: *\r\n";
    response += "\r\n";
    response += content;
    return response;
}

void EpollServer::sendResponse(int client_fd, const std::string& content) {
    std::string response = buildHttpResponse(content);
    write(client_fd, response.c_str(), response.length());
}