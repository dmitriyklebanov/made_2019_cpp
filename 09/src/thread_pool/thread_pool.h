#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include <utility>

class ThreadPool {
 private :
    enum class State {
        Starting,
        Started,
        Stopping,
        Stopped
    };

 private :
    std::vector<std::thread> pool_;
    std::mutex worker_cv_mtx_;
    std::condition_variable queue_cv_;
    std::condition_variable active_workers_cv_;
    std::vector<std::function<void()>> queue_;
    size_t active_workers_ = 0;
    State state_ = State::Stopped;

 private :
    void work();

 public :
    explicit ThreadPool(const size_t n);
    ~ThreadPool();

    void start();
    void wait();
    void stop();

    size_t active();

    template <class TFunc, class... Args>
    auto exec(TFunc func, Args... args) -> std::future<decltype(func(args...))>;
};

template <class TFunc, class... Args>
auto ThreadPool::exec(TFunc func, Args... args) -> std::future<decltype(func(args...))> {
    std::future<decltype(func(args...))> result;
    {
        std::lock_guard<std::mutex> lock(worker_cv_mtx_);
        auto exec_func = std::bind(std::move(func), std::move(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(func(args...))()>>(
            std::move(exec_func));
        result = task_ptr->get_future();

        queue_.push_back([task_ptr]() {
            (*task_ptr)();
        });
    }
    queue_cv_.notify_one();
    return result;
}
