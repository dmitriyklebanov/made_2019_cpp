#pragma once

#include <istream>
#include <string>
#include <utility>

#include "errors.hpp"

class Deserializer {
 private :
    static constexpr char Separator_ = ' ';

    std::istream& in_;
 public :
    explicit Deserializer(std::istream& in);

    template <class T>
    Error load(T& obj);

    template <typename... Args>
    Error operator()(Args&&... args);

 private:
    template <class T>
    Error deserialize(T& obj);

    template <class T>
    Error process(T& obj);

    template <class T, typename... Args>
    Error process(T& obj, Args&&... args);
};

Deserializer::Deserializer(std::istream& in)
    : in_(in)
{
}

template <class T>
Error Deserializer::load(T& obj) {
    return deserialize(obj);
}

template <typename... Args>
Error Deserializer::operator()(Args&&... args) {
    return process(std::forward<Args>(args)...);
}

template <class T>
Error Deserializer::deserialize(T& obj) {
    return obj.deserialize(*this);
}

template <>
Error Deserializer::deserialize(bool& obj) {
    std::string text;
    in_ >> text;
    if (text == "true") {
        obj = true;
    } else if (text == "false") {
        obj = false;
    } else {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

template <>
Error Deserializer::deserialize(uint64_t& obj) {
    in_ >> obj;
    return Error::NoError;
}

template <class T>
Error Deserializer::process(T& obj) {
    return deserialize(obj);
}

template <class T, typename... Args>
Error Deserializer::process(T& obj, Args&&... args) {
    Error result = deserialize(obj);
    if (result == Error::NoError) {
        return process(std::forward<Args>(args)...);
    }
    return result;
}
