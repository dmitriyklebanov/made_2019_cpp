#include <functional>

#include "expression/expression.h"
#include "lib/tester.hpp"

int test() {
    using TestFunc = std::function<bool(const std::string&, const int, const bool)>;
    TestFunc test_func =
        [](const std::string& expression, const int ans, const bool thrown_exception) {
            int res = 0;
            try {
                Expression expr;
                expr.parseFromString(expression);
                res = expr.evaluate();
            } catch (...) {
                return thrown_exception;
            }
            return res == ans;
        };
    Tester<TestFunc>expression_tester(test_func);

    expression_tester.execute("", 0, false);
    expression_tester.execute("-1 +2-3+4 -5+6-7", -4, false);
    expression_tester.execute("-1+002 - 3*4/5*6/7", 0, false);
    expression_tester.execute("-1+2-3*4/5* 6 /  7 l", 0, true);
    expression_tester.execute("-1 + 2/ 3 - 10/5 - -6/2", 0, false);
    expression_tester.execute("5 + 8* -4/0", 0, true);
    expression_tester.execute("2+-1-5*2", -9, false);
    expression_tester.execute("10/2*3+1", 16, false);
    expression_tester.execute("10+8--1", 19, false);
    expression_tester.execute("10+8---1", 0, true);
    expression_tester.execute("10++8--1", 0, true);
    expression_tester.execute("5+12/-3-5", -4, false);
    expression_tester.execute("5+", 0, true);
    expression_tester.execute("+5", 0, true);
    expression_tester.execute("1/0", 0, true);

    expression_tester.printStatistics();
    return expression_tester.getTotal() != expression_tester.getSuccess();
}

int main() {
    return test();
}
