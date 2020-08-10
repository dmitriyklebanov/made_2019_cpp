#pragma once

#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

template <class T>
std::string toString(const T& val) {
    std::stringstream stream;
    stream << val;
    return stream.str();
}

size_t toSizeT(const std::string& str) {
    size_t res = 0;
    size_t i = 0;
    while (i < str.size() && '0' <= str[i] && str[i] <= '9') {
        size_t max_val = (std::numeric_limits<size_t>::max() - (str[i] - '0')) / 10;
        if (res > max_val) {
            throw std::runtime_error("toSizeT(): overflow");
        }
        res *= 10;
        res += str[i] - '0';
        i++;
    }
    if (i != str.size()) {
        throw std::runtime_error("toSizeT(): invalid sign");
    }
    return res;
}


template <class T>
void argsToString(std::vector<std::string>& res, const T& value) {
    res.push_back(toString(value));
}


template <class T, typename... Args>
void argsToString(std::vector<std::string>& res, const T& value, Args&&... args) {
    res.push_back(toString(value));
    argsToString(res, std::forward<Args>(args)...);
}

std::string format(const std::string& format_str) {
    if (format_str.find("{") != std::string::npos ||
        format_str.find("}") != std::string::npos)
    {
        throw std::runtime_error("format(): error in format string:"
                                 "found unexpected control sign(s) {}");
    }
    return format_str;
}

template <typename... Args>
std::string format(const std::string& format_str, Args&&... args) {
    std::vector<std::string> strArgs;
    argsToString(strArgs, std::forward<Args>(args)...);

    std::string ans;
    size_t i = 0;
    while (i < format_str.size() && format_str.find("{", i) != std::string::npos) {
        size_t l = format_str.find("{", i);
        ans += format_str.substr(i, l - i);
        if (format_str.find("}", l) != std::string::npos) {
            size_t r = format_str.find("}", l);
            size_t id = toSizeT(format_str.substr(l + 1, r - l - 1));
            if (id >= strArgs.size()) {
                throw std::runtime_error("format(): argument not found");
            }
            ans += strArgs[id];
            i = r + 1;
        } else {
            throw std::runtime_error("format(): error in format string:"
                                     "not found control sign }");
        }
    }
    ans += format_str.substr(i, format_str.size() - i);

    return ans;
}
