#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <future>
#include <condition_variable>
#include <atomic>

class MyThreadPool {
public:
    explicit MyThreadPool(size_t threadCount) : stopFlag(false) {
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    // 获取任务
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        cv.wait(lock, [this] { return stopFlag || !tasks.empty(); });
                        if (stopFlag && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    // 执行任务
                    task();
                }
            });
        }
    }

    ~MyThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stopFlag = true;
        }
        cv.notify_all();
        for (std::thread &worker : workers) {
            if (worker.joinable())
                worker.join();
        }
    }

    // 提交任务，返回future
    template<typename Func, typename... Args>
    auto submit(Func&& func, Args&&... args)
        -> std::future<typename std::invoke_result_t<Func, Args...>> 
    {
        using ReturnType = typename std::invoke_result_t<Func, Args...>;

        auto taskPtr = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

        std::future<ReturnType> future = taskPtr->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stopFlag)
                throw std::runtime_error("ThreadPool has stopped");
            tasks.emplace([taskPtr]() { (*taskPtr)(); });
        }
        cv.notify_one();
        return future;
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable cv;
    bool stopFlag;
};

// 简单测试
int main() {
    MyThreadPool pool(4);

    auto f1 = pool.submit([](int a, int b) { 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return a + b; 
    }, 2, 3);

    auto f2 = pool.submit([]() {
        std::cout << "Hello from thread pool!" << std::endl;
    });

    std::cout << "Sum result: " << f1.get() << std::endl;
    f2.get(); // 等待f2完成

    return 0;
}
