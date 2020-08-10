#include <functional>
#include <sstream>
#include <string>

#include "lib/tester.hpp"
#include "lib/testlib.hpp"
#include "serializer/serializer.h"

int serializerTest() {
    using SerialiserTestFunc = std::function<bool(const std::string&,
        const Struct2&, const bool)>;
    SerialiserTestFunc serializer_test_func = [](
        const std::string& ans,
        const Struct2& to_serialize,
        const bool corrupted)
        {
            std::stringstream stream;
            Serializer serializer(stream);
            if (serializer.save(to_serialize) == Error::CorruptedArchive) {
                return corrupted;
            }
            return ans == stream.str() && !corrupted;
        };
    Tester<SerialiserTestFunc> serializer_test(serializer_test_func);

    Struct2 test;
    test.b1 = true;
    test.ui1 = 123;
    test.s1.ui1 = 456;
    test.s1.b1 = false;
    test.s1.ui2 = 789;
    test.s1.b2 = true;

    serializer_test.execute("true 123 456 false 789 true ", test, false);

    test.b1 = false;
    test.ui1 = 0;
    test.s1.ui1 = 1;
    test.s1.b1 = false;
    test.s1.ui2 = 2;
    test.s1.b2 = true;

    serializer_test.execute("false 0 1 false 2 true ", test, false);

    std::cout << "Serializer tests:\n";
    serializer_test.printStatistics();
    return serializer_test.getTotal() != serializer_test.getSuccess();
}


int main() {
    return serializerTest();
}
