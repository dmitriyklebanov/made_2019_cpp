#include "bigint.h"

#include <algorithm>
#include <cstdlib>  // long long abs(long long n)
#include <string>
#include <utility>

int BigInt::cmp(const BigInt& lhs, const BigInt& rhs) {
    if (lhs.sign_ > rhs.sign_) {
        return -1;
    }
    if (lhs.sign_ < rhs.sign_) {
        return 1;
    }

    int flag = (lhs.sign_ ? -1 : 1);

    if (lhs.elements_.size() < rhs.elements_.size()) {
        return flag * (-1);
    }
    if (lhs.elements_.size() > rhs.elements_.size()) {
        return flag * 1;
    }

    for (int i = lhs.elements_.size() - 1; i >= 0; --i) {
        if (lhs.elements_[i] < rhs.elements_[i]) {
            return flag * (-1);
        }

        if (lhs.elements_[i] > rhs.elements_[i]) {
            return flag * 1;
        }
    }

    return 0;
}

BigInt::BigInt(uint64_t number) {
    while (number) {
        elements_.push_back(number % 10);
        number /= 10;
    }
}

BigInt::BigInt(int64_t number)
    : BigInt(static_cast<uint64_t>(std::abs(number)))
{
    sign_ = number < 0;
}

BigInt& BigInt::operator +=(const BigInt& obj) {
    if (sign_ != obj.sign_) {
        sign_ ^= 1;
        (*this) -= obj;
        if (!elements_.empty()) {
            sign_ ^= 1;
        }
        return (*this);
    }
    int c = 0;
    size_t i = 0;
    elements_.resize(std::max(elements_.size(), obj.elements_.size()), 0);
    for (; i < std::min(elements_.size(), obj.elements_.size()); i++) {
        elements_[i] += obj.elements_[i] + c;
        c = elements_[i] > 9;
        elements_[i] %= 10;
    }

    for (; i < elements_.size(); i++) {
        elements_[i] += c;
        c = elements_[i] > 9;
        elements_[i] %= 10;
    }

    if (c) {
        elements_.push_back(c);
    }

    return *this;
}

BigInt& BigInt::operator -=(const BigInt& obj) {
    if (sign_ != obj.sign_) {
        sign_ ^= 1;
        (*this) += obj;
        if (!elements_.empty()) {
            sign_ ^= 1;
        }
        return *this;
    }

    if (sign_) {
        BigInt tmp = abs(obj);
        sign_ ^= 1;
        tmp -= (*this);
        (*this) = std::move(tmp);
        return *this;
    }

    if ((*this) < obj) {
        BigInt tmp = abs(obj);
        tmp -= (*this);
        (*this) = std::move(tmp);
        sign_ = 1;
        return *this;
    }

    int c = 0;
    size_t i = 0;
    elements_.resize(std::max(elements_.size(), obj.elements_.size()), 0);
    for (; i < std::min(elements_.size(), obj.elements_.size()); i++) {
        elements_[i] -= obj.elements_[i] + c;
        c = elements_[i] < 0;
        elements_[i] += 10 * c;
    }

    for (; i < elements_.size(); i++) {
        elements_[i] -= c;
        c = elements_[i] < 0;
        elements_[i] += 10 * c;
    }

    sign_ ^= c;

    while (!elements_.empty() && elements_.back() == 0) {
        elements_.pop_back();
    }

    return *this;
}

BigInt BigInt::operator -() const {
    BigInt tmp = *this;
    if (!elements_.empty()) {
        tmp.sign_ ^= 1;
    }
    return tmp;
}

BigInt operator +(const BigInt& lhs, const BigInt& rhs) {
    BigInt tmp(lhs); tmp += rhs;
    return tmp;
}

BigInt operator -(const BigInt& lhs, const BigInt& rhs) {
    BigInt tmp(lhs); tmp -= rhs;
    return tmp;
}


bool operator ==(const BigInt& lhs, const BigInt& rhs) {
    return (BigInt::cmp(lhs, rhs) == 0);
}

bool operator !=(const BigInt& lhs, const BigInt& rhs) {
    return (BigInt::cmp(lhs, rhs) != 0);
}

bool operator <(const BigInt& lhs, const BigInt& rhs) {
    return (BigInt::cmp(lhs, rhs) == -1);
}

bool operator >(const BigInt& lhs, const BigInt& rhs) {
    return (BigInt::cmp(lhs, rhs) == 1);
}

bool operator <=(const BigInt& lhs, const BigInt& rhs) {
    return (BigInt::cmp(lhs, rhs) != 1);
}

bool operator >=(const BigInt& lhs, const BigInt& rhs) {
    return (BigInt::cmp(lhs, rhs) != -1);
}

BigInt abs(const BigInt& obj) {
    BigInt ans = obj;
    ans.sign_ = 0;
    return ans;
}

std::istream& operator >>(std::istream& is, BigInt& obj) {
    std::string s; is >> s;
    if (s.empty()) {
        return is;
    }

    obj.sign_ = s[0] == '-';
    obj.elements_.reserve(s.size());
    for (int i = s.size() - 1; i >= static_cast<int>(obj.sign_); --i) {
        if ('0' <= s[i] && s[i] <= '9') {
            obj.elements_.push_back(s[i] - '0');
        } else {
            throw std::runtime_error("parser error: bad character");
        }
    }
    return is;
}

std::ostream& operator <<(std::ostream& os, const BigInt& obj) {
    if (obj.sign_) {
        os << '-';
    }

    for (int i = obj.elements_.size() - 1; i >= 0; --i) {
        os << char(obj.elements_[i] + '0');
    }
    return os;
}
