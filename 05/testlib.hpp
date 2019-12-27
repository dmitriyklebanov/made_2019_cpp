#pragma once

#include <cstdint>

#include "errors.hpp"

struct Struct1 {
    uint64_t ui1 = 0;
    bool b1 = false;
    uint64_t ui2 = 0;
    bool b2 = false;

    template <class Serializer>
    Error serialize(Serializer& serializer) const {
        return serializer(ui1, b1, ui2, b2);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer) {
        return deserializer(ui1, b1, ui2, b2);
    }
};

struct Struct2 {
    bool b1 = false;
    uint64_t ui1 = 0;
    Struct1 s1;

    template <class Serializer>
    Error serialize(Serializer& serializer) const {
        return serializer(b1, ui1, s1);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer) {
        return deserializer(b1, ui1, s1);
    }
};

bool operator ==(const Struct1& lhs, const Struct1& rhs) {
    return lhs.b1 == rhs.b1 && lhs.ui1 == rhs.ui1 && lhs.b2 == rhs.b2 && lhs.ui2 == rhs.ui2;
}

bool operator ==(const Struct2& lhs, const Struct2& rhs) {
    return lhs.b1 == rhs.b1 && lhs.ui1 == rhs.ui1 && lhs.s1 == rhs.s1;
}
