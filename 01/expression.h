#pragma once

#include <string>
#include <vector>

class Expression {
 private :
    static const char END_OF_EXPRESSION;
    static const std::vector<std::string> OPERATIONS;

 private :
    std::vector<int> _numbers_;
    std::vector<char> _operations_;

 private :
    void removeSpaces(std::string& expr);

    bool isDigit(const char c);
    bool isOperationWithPriority(const char sign, const size_t priority) const;

    bool containsInOperations(const char c);

    int parseNumber(const std::string& expr_str, size_t& pos);
    char parseSign(const std::string& expr_str, size_t& pos);

    int evaluateOperation(const int val1, const int val2, const char operation) const;
    int evaluateExpressionImpl(const size_t l, const size_t r) const;

 public :
    void parseFromString(std::string expr_str);
    int evaluate() const;

    void printDebug() const;
};
