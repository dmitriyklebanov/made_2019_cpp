#include "expression.h"

#include <iostream>
#include <stdexcept>

const char Expression::END_OF_EXPRESSION = '\n';
const std::vector<std::string> Expression::OPERATIONS = {"*/", "+-"};

void Expression::removeSpaces(std::string& expr) {
    std::string ans;
    ans.reserve(expr.size());
    for (const char c : expr) {
        if (c != ' ') {
            ans.push_back(c);
        }
    }
    expr = std::move(ans);
}

bool Expression::isDigit(const char c) {
    return ('0' <= c && c <= '9');
}

bool Expression::isOperationWithPriority(const char sign, const size_t priority) const {
    if (priority >= OPERATIONS.size()) {
        return false;
    }
    return OPERATIONS[priority].find(sign) != std::string::npos;
}

bool Expression::containsInOperations(const char c) {
    for (size_t i = 0; i < OPERATIONS.size(); i++) {
        if (isOperationWithPriority(c, i)) {
            return true;
        }
    }
    return false;
}

int Expression::parseNumber(const std::string& expr_str, size_t& pos) {
    if (pos == expr_str.size()) {
        throw std::out_of_range("end of expression string");
    }

    int number = 0;
    int number_sign = 1;

    if (expr_str[pos] == '-') {
        number_sign = -1;
        pos++;
    }
    int number_length = 0;
    while (pos < expr_str.size() && isDigit(expr_str[pos])) {
        number *= 10;
        number += expr_str[pos] - '0';
        number_length++;
        pos++;
    }

    if (number_length == 0) {
        if (pos == expr_str.size()) {
            throw std::length_error("length of number length in string representation can\'t be 0");
        } else {
            throw std::runtime_error("bad character");
        }
    }

    return number * number_sign;
}

char Expression::parseSign(const std::string& expr_str, size_t& pos) {
    if (pos == expr_str.size()) {
        throw std::out_of_range("end of expression string");
    }

    if (!containsInOperations(expr_str[pos])) {
        throw std::runtime_error("bad character");
    }

    return expr_str[pos++];
}

int Expression::evaluateOperation(const int val1, const int val2, const char operation) const {
    //std::cout << "eval = " << val1 << " " << val2 << " " << operation << std::endl;
    switch (operation) {
        case '+':
            return val1 + val2;
        case '-':
            return val1 - val2;
        case '*':
            return val1 * val2;
        case '/':
            if (val2 == 0) {
                throw std::runtime_error("division by zero");
            }
            return val1 / val2;
    }
    return 0;
}

int Expression::evaluateExpressionImpl(const size_t l, const size_t r) const {
    //std::cout << l << " " << r << std::endl;
    if (l == r) {
        return _numbers_[l];
    }
    size_t m = r - 1;
    while (m > l && isOperationWithPriority(_operations_[m], 0)) {
        m--;
    }
    if (isOperationWithPriority(_operations_[m], 0)) {
        m = r - 1;
    }
    //std::cout << m << std::endl;
    return evaluateOperation(
        evaluateExpressionImpl(l, m),
        evaluateExpressionImpl(m + 1, r),
        _operations_[m]
    );
}

void Expression::parseFromString(std::string expr_str) {
    removeSpaces(expr_str);
    if (expr_str.empty()) {
        return;
    }
    size_t pos = 0;
    while (pos < expr_str.size()) {
        int cur_number = parseNumber(expr_str, pos);
        char cur_operation = END_OF_EXPRESSION;
        if (pos != expr_str.size()) {
            cur_operation = parseSign(expr_str, pos);
        }
        _numbers_.push_back(cur_number);
        _operations_.push_back(cur_operation);
    }
    if (_operations_.back() != END_OF_EXPRESSION) {
        throw std::runtime_error("invalid end of expression");
    }
}

int Expression::evaluate() const {
    if (_numbers_.empty()) {
        return 0;
    }
    return evaluateExpressionImpl(0, _numbers_.size() - 1);
}

void Expression::printDebug() const {
    for (size_t i = 0; i < _numbers_.size(); i++) {
        std::cerr << _numbers_[i] << " | " << _operations_[i] << "/";
        //std::cerr << _numbers_[i] << _operations_[i];
    }
    std::cerr << std::endl;
}
