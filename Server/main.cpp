#include "EpollServer.h"
#include <signal.h>

EpollServer* server = nullptr;

void signalHandler(int signum) {
    if (server) {
        std::cout << "\n接收到信号 " << signum << "，正在关闭服务器..." << std::endl;
        server->stop();
    }
}

int main() {
    try {
        // 设置信号处理
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);

        // 创建并启动服务器
        server = new EpollServer(8080);  // 使用8080端口
        std::cout << "服务器已启动，按Ctrl+C退出" << std::endl;
        std::cout << "你需要登录才能进入服务器" << std::endl;

        
        server->run();

        delete server;
        server = nullptr;

    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        if (server) {
            delete server;
            server = nullptr;
        }
        return 1;
    }

    return 0;
}