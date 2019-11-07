#include "parser.h"

#include <sstream>

bool Parser::toInt(const std::string& str, int& value) {
    int sign = 1;
    size_t i = 0;
    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    for (; i < str.size(); i++) {
        if ('0' <= str[i] && str[i] <= '9') {
            value *= 10;
            value += str[i] - '0';
        } else {
            break;
        }
    }

    value *= sign;
    return i == str.size();
}

Parser::Parser(const std::string& str)
    : to_parse_(str)
{
}

Parser::Parser(std::string&& str)
    : to_parse_(std::move(str))
{
}

void Parser::setParseString(const std::string& str) {
    to_parse_ = str;
}

void Parser::setParseString(std::string&& str) {
    to_parse_ = std::move(str);
}

const std::string& Parser::getParseString() const {
    return to_parse_;
}

Parser& Parser::registerOnStart(Callback func) {
    on_start_.emplace_back(func);
    return *this;
}

Parser& Parser::registerOnFinish(Callback func) {
    on_finish_.emplace_back(func);
    return *this;
}

Parser& Parser::registerOnToken(StringTokenCallback func) {
    on_string_token_.emplace_back(func);
    return *this;
}

Parser& Parser::registerOnToken(IntTokenCallback func) {
    on_int_token_.emplace_back(func);
    return *this;
}

void Parser::parse(const std::string& str) {
    setParseString(str);
    parse();
}

void Parser::parse(std::string&& str) {
    setParseString(std::move(str));
    parse();
}

void Parser::parse() {
    onCallback(on_start_);

    std::stringstream stream;
    stream << to_parse_;

    std::string stringToken;
    while (stream >> stringToken) {
        int intToken = 0;
        if (toInt(stringToken, intToken)) {
            onTokenCallback(on_int_token_, std::move(intToken));
        } else {
            onTokenCallback(on_string_token_, std::move(stringToken));
        }
    }

    onCallback(on_finish_);
}
