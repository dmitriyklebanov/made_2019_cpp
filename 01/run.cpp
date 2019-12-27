#include <iostream>
#include <string>
#include <stdexcept>

#include "expression.h"

int run(const std::string& expr_str) {
    Expression expr;
    int res = 0;
    try {
        expr.parseFromString(expr_str);
        res = expr.evaluate();
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
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
