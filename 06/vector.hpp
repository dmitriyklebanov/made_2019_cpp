#pragma once

#include <stdexcept>

template <class T>
class Vector {
private :
    size_t buffer_size_ = 0;
    T* buffer_ = nullptr;
    size_t size_ = 0;

private :
    static T* allocate(const size_t size);

    void destroy();
    void resize_buffer(const size_t new_size);

public :
    Vector() = default;
    Vector(const Vector& obj);
    Vector(Vector&& obj);
    ~Vector();

    Vector& operator =(const Vector& obj);
    Vector& operator =(Vector&& obj);

    Vector(const size_t size);

    void resize(const size_t new_size);
    void resize(const size_t new_size, const T& value);
    void reserve(const size_t size);

    size_t size() const;
    bool empty() const;

    void push_back(const T& value);
    void pop_back();

    T& back();

    T& operator[](const size_t index);
    const T& operator[](const size_t index) const;
};

template <class T>
T* Vector<T>::allocate(const size_t size) {
    if (!size) {
        return nullptr;
    }
    T* res = static_cast<T*>(malloc(sizeof(T) * size));
    if (!res) {
        throw std::runtime_error("Vector<T>::allocate(): can\'t allocate memory");
    }
    return res;
}

template <class T>
void Vector<T>::destroy() {
    if (buffer_ != nullptr) {
        free(buffer_);
    }
    buffer_size_ = 0;
    size_ = 0;
}

template <class T>
void Vector<T>::resize_buffer(const size_t new_buffer_size) {
    T* new_buffer = allocate(new_buffer_size);
    std::copy(buffer_, buffer_ + size_, new_buffer);

    size_t cur_size = size_;
    destroy();

    buffer_size_ = new_buffer_size;
    buffer_ = new_buffer;
    size_ = cur_size;
}

template <class T>
Vector<T>::Vector(const size_t size)
    : buffer_size_(size)
    , buffer_(allocate(size))
    , size_(size)
{
}

template <class T>
Vector<T>::Vector(const Vector& obj)
    : buffer_size_(obj.size_)
    , buffer_(allocate(obj.size_))
    , size_(obj.size_)
{
    if (obj.buffer_) {
        std::copy(obj.buffer_, obj.buffer_ + size_, buffer_);
    }
}

template <class T>
Vector<T>::Vector(Vector&& obj)
    : buffer_size_(obj.buffer_size_)
    , buffer_(obj.buffer_)
    , size_(obj.size_)
{
    obj.buffer_size_ = 0;
    obj.buffer_ = nullptr;
    obj.size_ = 0;
}

template <class T>
Vector<T>::~Vector() {
    destroy();
}

template <class T>
Vector<T>& Vector<T>::operator =(const Vector& obj) {
    if (this == &obj) {
        return *this;
    }
    T* new_buffer = allocate(obj.size_);
    if (obj.buffer_) {
        std::copy(obj.buffer_, obj.buffer_ + obj.size_, new_buffer);
    }

    destroy();
    buffer_size_ = obj.size_;
    buffer_ = new_buffer;
    size_ = obj.size_;
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator =(Vector&& obj) {
    buffer_size_ = obj.buffer_size_;
    buffer_ = obj.buffer_;
    size_ = obj.size_;

    obj.buffer_size_ = 0;
    obj.buffer_ = nullptr;
    obj.size_ = 0;
    return *this;
}

template <class T>
void Vector<T>::resize(const size_t new_size) {
    if (new_size > buffer_size_) {
        resize_buffer(new_size);
    }

    size_ = new_size;
}

template <class T>
void Vector<T>::resize(const size_t new_size, const T& value) {
    if (new_size > buffer_size_) {
        resize_buffer(new_size);
    }

    for (size_t i = size_; i < new_size; i++) {
        buffer_[i] = value;
    }
    size_ = new_size;
}

template <class T>
void Vector<T>::reserve(const size_t size) {
    if (size > buffer_size_) {
        resize_buffer(size);
    }
}

template <class T>
size_t Vector<T>::size() const {
    return size_;
}

template <class T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

template <class T>
void Vector<T>::push_back(const T& value) {
    if (size_ == buffer_size_) {
        resize_buffer(buffer_size_ ? buffer_size_ * 2 : 1);
    }

    buffer_[size_] = value;
    size_++;
}

template <class T>
void Vector<T>::pop_back() {
    if (size_ == 0) {
        throw std::length_error("container is empty");
    }
    size_--;
}

template <class T>
T& Vector<T>::back() {
    if (size_ == 0) {
        throw std::length_error("container is empty");
    }
    return buffer_[size_ - 1];
}

template <class T>
T& Vector<T>::operator[](const size_t index) {
    return buffer_[index];
}

template <class T>
const T& Vector<T>::operator[](const size_t index) const {
    return buffer_[index];
}
