#pragma once

#include <ostream>
#include <utility>

#include "lib/errors.hpp"

class Serializer {
 private :
    static constexpr char Separator_ = ' ';

    std::ostream& out_;
 public :
    explicit Serializer(std::ostream& out);

    template <class T>
    Error save(const T& obj);

    template <typename... Args>
    Error operator()(Args&&... args);

 private:
    template <class T>
    Error serialize(const T& obj);

    template <class T>
    Error process(const T& obj);

    template <class T, typename... Args>
    Error process(const T& obj, Args&&... args);
};

Serializer::Serializer(std::ostream& out)
    : out_(out)
{
}

template <class T>
Error Serializer::save(const T& obj) {
    return serialize(obj);
}

template <typename... Args>
Error Serializer::operator()(Args&&... args) {
    return process(std::forward<Args>(args)...);
}

template <class T>
Error Serializer::serialize(const T& obj) {
    return obj.serialize(*this);
}

template <>
Error Serializer::serialize(const bool& obj) {
    out_ << (obj ? "true" : "false") << Separator_;
    return Error::NoError;
}

template <>
Error Serializer::serialize(const uint64_t& obj) {
    out_ << obj << Separator_;
    return Error::NoError;
}

template <class T>
Error Serializer::process(const T& obj) {
    return serialize(obj);
}

template <class T, typename... Args>
Error Serializer::process(const T& obj, Args&&... args) {
    Error result = serialize(obj);
    if (result == Error::NoError) {
        return process(std::forward<Args>(args)...);
    }
    return result;
}
