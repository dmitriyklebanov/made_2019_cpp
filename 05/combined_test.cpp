#include "deserializer.h"
#include "serializer.h"
#include "testlib.hpp"

#include <iostream>
#include <sstream>

int combinedTest() {
    std::stringstream stream;
    Struct2 s2;
    s2.b1 = true;
    s2.ui1 = 9077;
    s2.s1.ui1 = 36;
    s2.s1.b1 = false;
    s2.s1.ui2 = 20127;
    s2.s1.b2 = true;

    Serializer serializer(stream);
    serializer.save(s2);
    if (serializer.save(s2) == Error::CorruptedArchive) {
        return 1;
    }

    Deserializer deserializer(stream);
    Struct2 d2;
    if (deserializer.load(d2) == Error::CorruptedArchive) {
        return 1;
    }

    bool is_ok = s2 == d2;
    std::cout << "Combined test is " << (is_ok ? "" : "not ") << "ok" << std::endl;
    return !is_ok;
}

int main() {
    return combinedTest();
}
