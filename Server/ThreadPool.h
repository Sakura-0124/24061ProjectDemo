#ifndef THREAD_POOL_H  // 防止头文件重复包含
#define THREAD_POOL_H

// 包含必要的头文件
#include <vector>       // 用于存储工作线程
#include <queue>        // 用于任务队列
#include <thread>       // 用于创建线程
#include <mutex>        // 用于互斥锁
#include <condition_variable>  // 用于条件变量
#include <functional>   // 用于std::function
#include <memory>       // 用于智能指针

// 线程池类定义
class ThreadPool {
public:
    // 构造函数，指定线程数量
    explicit ThreadPool(size_t threads);
    // 析构函数
    ~ThreadPool();

    // 禁止拷贝构造函数
    ThreadPool(const ThreadPool&) = delete;
    // 禁止赋值操作符
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 添加新任务到线程池的模板函数
    template<class F>
    void enqueue(F&& f);

private:
    std::vector<std::thread> workers;        // 工作线程容器
    std::queue<std::function<void()>> tasks; // 任务队列
    
    std::mutex queue_mutex;                  // 用于保护任务队列的互斥锁
    std::condition_variable condition;        // 用于线程同步的条件变量
    bool stop;                               // 停止标志
};

// 构造函数实现
inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
    // 创建指定数量的工作线程
    for(size_t i = 0; i < threads; ++i) {
        // 创建工作线程并添加到容器中
        workers.emplace_back(
            [this] {  // 工作线程的主要逻辑
                while(true) {  // 无限循环
                    std::function<void()> task;  // 用于存储任务
                    {  // 作用域锁
                        // 获取任务队列的互斥锁
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // 等待条件变量
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->tasks.empty(); });
                        // 如果线程池停止且任务队列为空，退出线程
                        if(this->stop && this->tasks.empty())
                            return;
                        // 获取任务队列中的第一个任务
                        task = std::move(this->tasks.front());
                        this->tasks.pop();  // 移除已获取的任务
                    }
                    task();  // 执行任务
                }
            }
        );
    }
}

// 添加新任务的模板函数实现
template<class F>
void ThreadPool::enqueue(F&& f) {
    {  // 作用域锁
        // 获取任务队列的互斥锁
        std::unique_lock<std::mutex> lock(queue_mutex);
        // 如果线程池已停止，抛出异常
        if(stop) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        // 将任务添加到任务队列
        tasks.emplace(std::forward<F>(f));
    }
    // 通知一个等待的线程
    condition.notify_one();
}

// 析构函数实现
inline ThreadPool::~ThreadPool() {
    {  // 作用域锁
        // 获取任务队列的互斥锁
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;  // 设置停止标志
    }
    // 通知所有等待的线程
    condition.notify_all();
    // 等待所有工作线程完成
    for(std::thread &worker: workers) {
        worker.join();
    }
}

#endif  