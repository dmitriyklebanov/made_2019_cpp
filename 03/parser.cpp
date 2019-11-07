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

Parser& Parser::registerOnStart(Callback func) {
    on_start_.emplace_back(std::move(func));
    return *this;
}

Parser& Parser::registerOnFinish(Callback func) {
    on_finish_.emplace_back(std::move(func));
    return *this;
}

Parser& Parser::registerOnToken(StringTokenCallback func) {
    on_string_token_.emplace_back(std::move(func));
    return *this;
}

Parser& Parser::registerOnToken(IntTokenCallback func) {
    on_int_token_.emplace_back(std::move(func));
    return *this;
}

void Parser::parse(std::string to_parse) {
    onCallback(on_start_);

    std::stringstream stream;
    stream << std::move(to_parse);

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
