#pragma once

#include <sstream>
#include <string>

template <int N>
void validateFormattedString(const std::string&) {
}

template <>
void validateFormattedString<0>(const std::string& str) {
    if (str.find("{") != std::string::npos ||
        str.find("}") != std::string::npos)
    {
        throw std::runtime_error("format(): error in format string: found unexpected control sign(s) {}");
    }
}

template <class T>
std::string toString(const T& val) {
    std::stringstream stream;
    stream << val;
    return stream.str();
}

template <int N = 0, class T>
std::string format(const std::string& format_str, const T& cur_val) {
    std::string ans;
    std::string arg = std::string("{") + toString(N) + "}";
    size_t i = 0;
    while (format_str.find(arg, i) != std::string::npos) {
        int j = format_str.find(arg, i);
        ans += format_str.substr(i, j - i);
        ans += toString(cur_val);
        i = j + arg.size();
    }
    ans += format_str.substr(i, format_str.size() - i);
    validateFormattedString<N>(ans);
    return ans;
}


template <int N = 0, class T, typename... Args>
std::string format(const std::string& input, const T& cur_val, Args&&... args) {
    std::string res = format<N + 1>(input, std::forward<Args>(args)...);
    return format<N>(res, cur_val);
}
