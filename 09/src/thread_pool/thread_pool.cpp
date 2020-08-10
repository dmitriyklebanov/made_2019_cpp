#include "thread_pool.h"

#include <atomic>
#include <stdexcept>

void ThreadPool::work() {
    while (true) {
        std::unique_lock<std::mutex> lock(worker_cv_mtx_);
        --active_workers_;
        active_workers_cv_.notify_all();

        queue_cv_.wait(lock, [this]() {
            return !queue_.empty() || state_ == State::Stopping;
        });
        if (state_ == State::Stopping) {
            break;
        }

        ++active_workers_;
        active_workers_cv_.notify_all();

        auto func = std::move(queue_.back());
        queue_.pop_back();
        lock.unlock();
        func();
    }
}


ThreadPool::ThreadPool(const size_t n)
    : pool_(n)
{
    if (n == 0) {
        throw std::runtime_error("ThreadPool::ThreadPool():"
                "number of threads should be more than zero.");
    }
}

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::start() {
    if (state_ == State::Stopped) {
        state_ = State::Starting;
        active_workers_ = pool_.size();
        for (auto& worker : pool_) {
            worker = std::thread(&ThreadPool::work, this);
        }
        atomic_thread_fence(std::memory_order_release);
        state_ = State::Started;
    }
}

void ThreadPool::wait() {
    std::unique_lock<std::mutex> lock(worker_cv_mtx_);
    active_workers_cv_.wait(lock, [this]() {
        return queue_.empty() && !active_workers_;
    });
}

void ThreadPool::stop() {
    if (state_ == State::Started) {
        state_ = State::Stopping;
        queue_cv_.notify_all();
        for (auto& worker : pool_) {
            worker.join();
        }
        atomic_thread_fence(std::memory_order_release);
        state_ = State::Stopped;
    }
}

size_t ThreadPool::active() {
    std::lock_guard<std::mutex> lock(worker_cv_mtx_);
    return active_workers_;
}
