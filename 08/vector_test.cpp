#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>

#include "tester.hpp"
#include "vector.hpp"

bool resizeTest() {
    Vector<int> a;
    size_t real_capacity = 0;
    if (a.capacity() != real_capacity) {
        return false;
    }
    for (size_t i = 0; i < 1000; i++) {
        a.push_back(i);
        if (real_capacity == i) {
            if (i == 0) {
                real_capacity++;
            } else {
                real_capacity *= 2;
            }
        }
        if (real_capacity != a.capacity()) {
            return false;
        }
    }
    for (size_t i = 0; i < 1000; i++) {
        a.pop_back();
    }
    if (real_capacity != a.capacity()) {
        return false;
    }
    a.resize(1024);
    if (real_capacity != a.capacity()) {
        return false;
    }
    a.clear();
    if (real_capacity != a.capacity()) {
        return false;
    }
    a.resize(2000);
    if (2000 != a.capacity()) {
        return false;
    }
    a = Vector<int>(20);
    if (20 != a.capacity()) {
        return false;
    }
    return true;
}

bool iteratorTest() {
    Vector<int> a(100);
    for (int i = 0; i < 100; i++) {
        a[i] = i;
    }
    int i = 99;
    for (auto it = a.crbegin(); it != a.crend(); it++, i--) {
        if (*it != i) {
            return false;
        }
    }
    return true;
}

bool popBackTest() {
    Vector<int> a(1000);
    for (size_t i = 0; i < 1000; i++) {
        a.pop_back();
    }
    try {
        a.pop_back();
    } catch (const std::length_error& ex) {
    }
    return true;
}

int vectorTest() {
    Tester vector_test;
    vector_test.execute(resizeTest);
    vector_test.execute(iteratorTest);
    vector_test.execute(popBackTest);
    vector_test.printStatistics();
    return vector_test.getTotal() != vector_test.getSuccess();
}


int main() {
    return vectorTest();
}
