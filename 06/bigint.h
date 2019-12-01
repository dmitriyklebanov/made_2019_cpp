#pragma once

#include "utils/vector.hpp"

#include <iostream>

class BigInt {
private :
    using ElementType = char;
    Vector<ElementType> elements_;
    bool sign_ = false;

private :
    static int cmp(const BigInt& lhs, const BigInt& rhs);

public :
    BigInt() = default;

    BigInt(unsigned long long number);
    BigInt(long long number);

    BigInt& operator +=(const BigInt& obj);
    BigInt& operator -=(const BigInt& obj);

    BigInt operator -() const;

    friend bool operator ==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator !=(const BigInt& lhs, const BigInt& rhs);

    friend bool operator <(const BigInt& lhs, const BigInt& rhs);
    friend bool operator >(const BigInt& lhs, const BigInt& rhs);
    friend bool operator <=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator >=(const BigInt& lhs, const BigInt& rhs);

    friend BigInt abs(const BigInt& obj);

    friend std::istream& operator >>(std::istream& is, BigInt& obj);
    friend std::ostream& operator <<(std::ostream& os, const BigInt& obj);
};

BigInt operator +(const BigInt& lhs, const BigInt& rhs);
BigInt operator -(const BigInt& lhs, const BigInt& rhs);
