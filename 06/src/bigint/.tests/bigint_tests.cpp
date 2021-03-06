#include <functional>
#include <iostream>
#include <random>

#include "bigint/bigint.h"
#include "lib/tester.hpp"

int bigIntTest() {
    using BigIntTestFunc = std::function<bool(const int64_t, const int64_t)>;
    BigIntTestFunc bigint_Test_func = [](
        const int64_t x,
        const int64_t y)
        {
            BigInt a = x;
            BigInt b = y;

            bool ans = true;

            ans &= ((a == b) == (x == y));
            ans &= ((a != b) == (x != y));
            ans &= ((a < b) == (x < y));
            ans &= ((a > b) == (x > y));
            ans &= ((a <= b) == (x <= y));
            ans &= ((a >= b) == (x >= y));
            ans &= (-a == -x);
            ans &= (-b == -y);
            ans &= (a + b == x + y);
            ans &= (a - b == x - y);

            return ans;
        };
    Tester<BigIntTestFunc> bigint_test(bigint_Test_func);

    bigint_test.execute(0, 0);
    bigint_test.execute(-1, 2);
    bigint_test.execute(1, -2);
    bigint_test.execute(1, 2);
    bigint_test.execute(-1, -2);

    std::mt19937_64 rnd(42);
    for (size_t i = 0; i < 99995; i++) {
        bigint_test.execute(rnd() % 1000000 - 500000, rnd() % 1000000 - 500000);
    }

    bigint_test.printStatistics();
    return bigint_test.getTotal() != bigint_test.getSuccess();
}


int main() {
    return bigIntTest();
}
