#pragma once

#include <iostream>
#include <vector>

class Tester {
private:
    int _total_ = 0;
    int _success_ = 0;
    std::vector<size_t> _failed_ids_;

public:
    template<typename... Args>
    void execute(const std::string& res, bool is_exc, Args&&... args);

    void printStatistics() const;
    int getTotal() const;
    int getSuccess() const;
};

template<typename... Args>
void Tester::execute(const std::string& res, bool is_exc, Args&&... args) {
    _total_++;
    bool is_success = false;
    try {
        const std::string ans = format(std::forward<Args>(args)...);
        is_success = ans == res;
        is_success ^= is_exc;
    } catch (...) {
        is_success = is_exc;
    }
    if (!is_success) {
        _failed_ids_.push_back(_total_);
    } else {
        _success_++;
    }

}

void Tester::printStatistics() const {
    std::cout << "total tests: " << _total_ << "\n";
    std::cout << "success: " << _success_ << "\n";
    if (_total_ != _success_) {
        std::cout << "ids of failed tests: ";
        for (const int id : _failed_ids_) {
            std::cout << id << " ";
        }
    }
}

int Tester::getTotal() const {
    return _total_;
}

int Tester::getSuccess() const {
    return _success_;
}
