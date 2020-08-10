#include <functional>
#include <sstream>
#include <string>

#include "deserializer/deserializer.h"
#include "lib/tester.hpp"
#include "lib/testlib.hpp"

int deserializerTest() {
    using DeserialiserTestFunc = std::function<bool(std::istream&, const Struct2&, const bool)>;
    DeserialiserTestFunc deserializer_test_func = [](
        std::istream& in,
        const Struct2& answer,
        const bool corrupted)
        {
            Deserializer deserializer(in);
            Struct2 result;
            if (deserializer.load(result) == Error::CorruptedArchive) {
                return corrupted;
            }
            return result == answer && !corrupted;
        };
    Tester<DeserialiserTestFunc> deserializer_test(deserializer_test_func);

    Struct2 test;
    test.b1 = true;
    test.ui1 = 123;
    test.s1.ui1 = 456;
    test.s1.b1 = false;
    test.s1.ui2 = 789;
    test.s1.b2 = true;

    std::stringstream stream("true 123 00456 false 789 true");
    deserializer_test.execute(stream, test, false);

    test.b1 = false;
    test.ui1 = 0;
    test.s1.ui1 = 0;
    test.s1.b1 = false;
    test.s1.ui2 = 0;
    test.s1.b2 = true;


    stream = std::stringstream("false 00 0 false 0 true");
    deserializer_test.execute(stream, test, false);

    stream = std::stringstream("false 0 0 false 0 tree");
    deserializer_test.execute(stream, test, true);
    stream = std::stringstream("0 0 0 false 0 true");
    deserializer_test.execute(stream, test, true);

    std::cout << "Deserializer tests:\n";
    deserializer_test.printStatistics();
    return deserializer_test.getTotal() != deserializer_test.getSuccess();
}

int main() {
    return deserializerTest();
}
