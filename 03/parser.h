#pragma once

#include <functional>
#include <string>
#include <vector>

class Parser {
public :
    using Callback = std::function<void()>;
    using StringTokenCallback = std::function<void(std::string)>;
    using IntTokenCallback = std::function<void(int)>;

private :
    std::string to_parse_;
    std::vector<Callback> on_start_;
    std::vector<Callback> on_finish_;
    std::vector<StringTokenCallback> on_string_token_;
    std::vector<IntTokenCallback> on_int_token_;

    template <typename Func>
    void onCallback(std::vector<Func>& callbacks);

    template <typename Token>
    void onTokenCallback(std::vector<std::function<void(Token)>>& callbacks, Token&& token);

    bool toInt(const std::string& str, int& value);
public :
    Parser() = default;
    ~Parser() = default;

    Parser(const std::string& str);
    Parser(std::string&& str);

    void setParseString(const std::string& str);
    void setParseString(std::string&& str);
    const std::string& getParseString() const;

    Parser& registerOnStart(Callback func);
    Parser& registerOnFinish(Callback func);
    Parser& registerOnToken(StringTokenCallback func);
    Parser& registerOnToken(IntTokenCallback func);

    void parse(const std::string& str);
    void parse(std::string&& str);
    void parse();
};

template <typename Func>
void Parser::onCallback(std::vector<Func>& callbacks) {
    for (auto& callback : callbacks) {
        callback();
    }
}

template <typename Token>
void Parser::onTokenCallback(std::vector<std::function<void(Token)>>& callbacks, Token&& token) {
    for (auto& callback : callbacks) {
        callback(std::move(token));
    }
}

