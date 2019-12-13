#pragma once

#include <iostream>
#include <vector>

class Tester {
private:
    int _total_ = 0;
    int _success_ = 0;
    std::vector<size_t> _failed_ids_;

public:
    template<class TFunc, typename... Args>
    void execute(TFunc&& func, Args&&... args);

    void printStatistics() const;
    int getTotal() const;
    int getSuccess() const;
};

template<class TFunc, typename... Args>
void Tester::execute(TFunc&& func, Args&&... args) {
    _total_++;
    bool res = func(std::forward<Args>(args)...);
    _success_ += res;
    if (!res) {
        _failed_ids_.push_back(_total_);
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
