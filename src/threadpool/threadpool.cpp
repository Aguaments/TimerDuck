//
// Created by g30067333 on 2025/3/12.
//
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <vector>
#include <queue>
#include <iostream>
#include <future>
#include <memory>
#include <Windows.h>

// 枚举类可以通过作用域限定符访问，避免了枚举值污染全局作用域
enum class TaskPriority {
    LOW,
    MEDIUM,
    HIGH
};

struct Task {
    std::function<void()> func;
    TaskPriority priority;
    std::chrono::milliseconds timeout; // 用于超时任务
    std::shared_ptr<std::promise<void>> cancelPromise; // 用于取消任务
    Task(std::function<void()> f, TaskPriority p, std::chrono::milliseconds t)
    : func(f), priority(p), timeout(t), cancelPromise(std::make_shared<std::promise<void>>()){}

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

class ThreadPool {
public:
    ThreadPool(size_t numThreads, size_t maxThreads)
    :stop(false), totalThreads(numThreads), maxThreads(maxThreads), activeThreads(0) {
        for(size_t i = 0; i < numThreads; ++ i) {
            workers.emplace_back([this]() {
                this -> workerThread();
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for(std::thread & worker: workers) {
            worker.join();
        }
    }

    template <typename F>
    void enqueue(F&& f, TaskPriority priority = TaskPriority::MEDIUM, std::chrono::milliseconds timeout = std::chrono::milliseconds(0)) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if(stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace(std::forward<F>(f), priority, timeout);
        }
        condition.notify_one();
    }

    void adjustThreadPoolSize() {
        double loadFactor = getCPUUsage();
        size_t targetThreads = static_cast<size_t>(maxThreads * loadFactor);
        if(targetThreads > totalThreads) {
            addThreads(targetThreads - totalThreads);
        }else if(targetThreads < totalThreads) {
            removeThread(totalThreads - targetThreads);
        }
    }

    size_t activeThreadCount() const{
        return activeThreads.load(); // load()函数返回当前原子对象的值，不指定参数的话默认最强的内存顺序，不会导致读写不一致问题
    }

private:
    void workerThread() {
        while(true) {
            std::function<void()> task;
            std::shared_ptr<std::promise<void>> cancelPromise;
            std::chrono::milliseconds timeout;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                if(stop && tasks.empty()) {
                    return ;
                }

                task = std::move(tasks.top().func);
                cancelPromise = tasks.top().cancelPromise;
                timeout = tasks.top().timeout;
                tasks.pop();

                ++ activeThreads;
            }

            if(timeout.count() > 0) {
                auto future = cancelPromise -> get_future();
                if(future.wait_for(timeout) == std::future_status::timeout) {
                    std::cout << "Task timed out, cancelling\n";
                    continue;
                }
            }

            task();
            -- activeThreads;
        }
    }

    void addThreads(size_t numThreads) {
        std::unique_lock<std::mutex> lock(queueMutex);
        for(auto i = 0; i < numThreads; ++i) {
            workers.emplace_back([this]() {
                this -> workerThread()();
            });
        }
        totalThreads += numThreads;
    }

    void removeThread(size_t numThreads) {
        std::unique_lock<std::mutex> lock(queueMutex);
        if(numThreads >= totalThreads) {
            stop = true;
        }
        totalThreads -= numThreads;
    }

    // Windows版本
    double getCPUUsage() {
        static ULONGLONG lastUserTime = 0, lastKernelTime = 0, lastIdleTime = 0;
        static ULONGLONG lastTime = 0;

        FILETIME idleTime, kernelTime, userTime;
        if(GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
            ULONGLONG idle = (((ULONGLONG)idleTime.dwHighDateTime) << 32) | idleTime.dwLowDateTime;
            ULONGLONG kernel = (((ULONGLONG)kernelTime.dwHighDateTime) << 32) | kernelTime.dwLowDateTime;
            ULONGLONG user = (((ULONGLONG)userTime.dwHighDateTime) << 32) | userTime.dwLowDateTime;

            if(lastTime != 0) {
                ULONGLONG sysIdle = idle - lastIdleTime;
                ULONGLONG sysKernel = kernel - lastKernelTime;
                ULONGLONG sysUser = user - lastUserTime;
                ULONGLONG sysTotal = sysIdle + sysUser + sysKernel;

                double cpuUsage = (sysKernel + sysUser) * 100.0 / sysTotal;

                lastIdleTime = idle;
                lastKernelTime = kernel;
                lastUserTime = user;

                return cpuUsage;
            }

            lastIdleTime = idle;
            lastKernelTime = kernel;
            lastUserTime = user;
            lastTime = 1;
        }
        return 0.0;
    }

    std::vector<std::thread> workers;
    std::priority_queue<Task> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    size_t totalThreads;
    size_t maxThreads;
    std::atomic<size_t> activeThreads;
};
