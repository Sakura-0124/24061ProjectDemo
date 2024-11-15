#ifndef EPOLL_SERVER_H
#define EPOLL_SERVER_H

#include "UserManager.h"
#include "JsonHandler.h"
#include "ThreadPool.h"
#include "General.h"

class EpollServer {
public:
    explicit EpollServer(int port);
    ~EpollServer();

    void run();
    void stop();

private:
    static const int MAX_EVENTS = 1024;
    static const int BUFFER_SIZE = 4096;
    
    int server_fd;
    int epoll_fd;
    bool running;
    ThreadPool thread_pool;
    JsonHandler json_handler;

    void setNonBlocking(int sock);
    void handleNewConnection();
    void handleClientData(int client_fd);
    void handleAdminAction(int client_fd, const Json::Value& json_request, bool isHttp);
    void handleJsonMessage(int client_fd, const Json::Value& json_request, bool isHttp);
    void handleTextMessage(int client_fd, const std::string& message);
    void sendResponse(int client_fd, const std::string& content);
    std::string getClientInfo(int client_fd);
    std::string buildHttpResponse(const std::string& content);
};

#endif