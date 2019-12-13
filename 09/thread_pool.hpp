#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

class ThreadPool {
private :
    std::vector<std::thread> _pool_;
    std::mutex _worker_cv_mtx_;
    std::condition_variable _queue_cv_;
    std::condition_variable _active_workers_cv_;
    std::vector<std::function<void()>> _queue_;
    size_t _active_workers_ = 0;
    bool _stopped_ = true;

    class ThreadWorker {
    private :
        ThreadPool& _pool_;
    public :
        ThreadWorker(ThreadPool& pool);

        void operator ()();
    };
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

ThreadPool::ThreadWorker::ThreadWorker(ThreadPool& pool)
    : _pool_(pool)
{
}

void ThreadPool::ThreadWorker::operator ()() {
    while (true) {
        std::unique_lock<std::mutex> lock(_pool_._worker_cv_mtx_);
        --_pool_._active_workers_;
        _pool_._active_workers_cv_.notify_all();

        _pool_._queue_cv_.wait(lock, [this]() {
            return !_pool_._queue_.empty() || _pool_._stopped_;
        });
        if (_pool_._stopped_) {
            break;
        }

        ++_pool_._active_workers_;
        _pool_._active_workers_cv_.notify_all();

        auto func = std::move(_pool_._queue_.back());
        _pool_._queue_.pop_back();
        lock.unlock();
        func();
    }
}


ThreadPool::ThreadPool(const size_t n)
    : _pool_(n)
{
    if (n == 0) {
        throw std::runtime_error("ThreadPool::ThreadPool(): number of threads should be more than zero.");
    }
}

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::start() {
    if (_stopped_) {
        _stopped_ = false;
        std::lock_guard<std::mutex> lock(_worker_cv_mtx_);
        _active_workers_ = _pool_.size();
        for (auto& worker : _pool_) {
            worker = std::thread(ThreadWorker(*this));
        }
    }
}

void ThreadPool::wait() {
    std::unique_lock<std::mutex> lock(_worker_cv_mtx_);
    _active_workers_cv_.wait(lock, [this]() {
        return _queue_.empty() && !_active_workers_;
    });
}

void ThreadPool::stop() {
    {
        std::lock_guard<std::mutex> lock(_worker_cv_mtx_);
        if (_stopped_) {
            return;
        }
        _stopped_ = true;
    }
    _queue_cv_.notify_all();
    for (auto& worker : _pool_) {
        worker.join();
        worker.~thread();
    }
}

size_t ThreadPool::active() {
    std::lock_guard<std::mutex> lock(_worker_cv_mtx_);
    return _active_workers_;
}

template <class TFunc, class... Args>
auto ThreadPool::exec(TFunc func, Args... args) -> std::future<decltype(func(args...))> {
    std::future<decltype(func(args...))> result;
    {
        std::lock_guard<std::mutex> lock(_worker_cv_mtx_);
        auto exec_func = std::bind(std::move(func), std::move(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::move(exec_func));
        result = task_ptr->get_future();

        _queue_.push_back([task_ptr]() {
            (*task_ptr)();
        });
    }
    _queue_cv_.notify_one();
    return result;
}
