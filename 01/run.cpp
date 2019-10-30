#include "expression.h"

#include <iostream>
#include <string>
#include <stdexcept>

int run(std::string&& expr_str) {
    Expression expr;
    try {
        expr.parseFromString(std::move(expr_str));
    } catch (const std::exception& ex) {
        std::cout << "Error when parsing expression from string: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unhandled exception" << std::endl;
        throw;
    }

    int res = 0;
    try {
        res = expr.evaluate();
    } catch (const std::exception& ex) {
        std::cout << "Error when evaluating expression: " << ex.what() << std::endl;
        return 2;
    } catch (...) {
        std::cout << "Unhandled exception" << std::endl;
        throw;
    }
    std::cout << "Result: " << res << std::endl;
    return 0;
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "Invalid arguments. Example:\n";
        std::cout << "run [expression]" << std::endl;
        return -1;
    }
    return run(std::string(argv[1]));
}
