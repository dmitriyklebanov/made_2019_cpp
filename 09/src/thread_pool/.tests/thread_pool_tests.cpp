#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>

#include "lib/tester.hpp"
#include "thread_pool/thread_pool.h"

uint64_t f(uint64_t n) {
    n *= 100000000LL;
    uint64_t ans = 0;
    for (uint64_t i = 0; i < n; i++) {
        ans += i;
        ans %= (1LL << 32);
    }
    return ans;
}

bool waitTest(const size_t n) {
    ThreadPool tp(n);
    tp.start();
    tp.exec(f, 1);
    tp.exec(f, 3);
    tp.exec(f, 5);
    tp.exec(f, 7);
    tp.exec(f, 9);
    tp.wait();
    std::cout << "waitTest has been finished" << std::endl;
    return true;
}

bool startStopTest() {
    {
        ThreadPool tp(10);
        tp.start();
        tp.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        tp.stop();
        tp.stop();
    }
    return true;
}

bool autoStopTest() {
    {
        ThreadPool tp(10);
        tp.start();
        tp.exec(f, 9);
    }
    return true;
}

int threadPoolTest() {
    Tester thread_pool_test;
    thread_pool_test.execute(waitTest, 1);
    thread_pool_test.execute(waitTest, 2);
    thread_pool_test.execute(waitTest, 5);
    thread_pool_test.execute(waitTest, 10);
    thread_pool_test.execute(startStopTest);
    thread_pool_test.execute(autoStopTest);
    thread_pool_test.printStatistics();
    return thread_pool_test.getTotal() != thread_pool_test.getSuccess();
}

int main() {
    return threadPoolTest();
}
