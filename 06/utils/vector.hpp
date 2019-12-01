#pragma once

#include <memory>
#include <stdexcept>

template <class T, class Allocator = std::allocator<T>>
class Vector {
private :
    size_t buffer_size_ = 0;
    T* buffer_ = nullptr;
    size_t size_ = 0;

    Allocator allocator_ = Allocator();

private :
    T* allocate(const size_t size);

    void destroy();
    void resize_buffer(const size_t new_size);

public :
    Vector() = default;
    Vector(Allocator allocator);
    Vector(const Vector& obj);
    Vector(Vector&& obj);
    ~Vector();

    Vector& operator =(const Vector& obj);
    Vector& operator =(Vector&& obj);

    void resize(const size_t new_size, const T& value);
    void reserve(const size_t size);

    size_t size() const;
    bool empty() const;

    void push_back(const T& value);
    void pop_back();

    T& back();

    T& operator[](const size_t index);
    const T& operator[](const size_t index) const;

    using iterator = T*;
    using const_iterator = const T*;

    iterator begin();
    const_iterator cbegin() const;

    iterator end();
    const_iterator cend() const;
};

template <class T, class Allocator>
T* Vector<T, Allocator>::allocate(const size_t size) {
    if (!size) {
        return nullptr;
    }
    T* res = allocator_.allocate(size);
    if (!res) {
        throw std::runtime_error("Vector<T>::allocate(): can\'t allocate memory");
    }
    return res;
}

template <class T, class Allocator>
void Vector<T, Allocator>::destroy() {
    if (buffer_ != nullptr) {
        allocator_.deallocate(buffer_, buffer_size_);
        buffer_ = nullptr;
    }
    buffer_size_ = 0;
    size_ = 0;
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize_buffer(const size_t new_buffer_size) {
    T* new_buffer = allocate(new_buffer_size);
    std::copy(buffer_, buffer_ + size_, new_buffer);

    size_t cur_size = size_;
    destroy();

    buffer_size_ = new_buffer_size;
    buffer_ = new_buffer;
    size_ = cur_size;
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(Allocator allocator)
    : allocator_(allocator)
{
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& obj)
    : buffer_size_(obj.size_)
    , buffer_(allocate(obj.size_))
    , size_(obj.size_)
    , allocator_(obj.allocator_)
{
    if (obj.buffer_) {
        std::copy(obj.buffer_, obj.buffer_ + size_, buffer_);
    }
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& obj)
    : buffer_size_(obj.buffer_size_)
    , buffer_(obj.buffer_)
    , size_(obj.size_)
    , allocator_(std::move(obj.allocator_))
{
    obj.buffer_size_ = 0;
    obj.buffer_ = nullptr;
    obj.size_ = 0;
}

template <class T, class Allocator>
Vector<T, Allocator>::~Vector() {
    destroy();
}

template <class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator =(const Vector& obj) {
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
    allocator_ = obj.allocator_;
    return *this;
}

template <class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator =(Vector&& obj) {
    buffer_size_ = obj.buffer_size_;
    buffer_ = obj.buffer_;
    size_ = obj.size_;
    allocator_ = std::move(obj.allocator_);

    obj.buffer_size_ = 0;
    obj.buffer_ = nullptr;
    obj.size_ = 0;
    return *this;
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize(const size_t new_size, const T& value) {
    if (new_size > buffer_size_) {
        resize_buffer(new_size);
    }

    for (size_t i = size_; i < new_size; i++) {
        buffer_[i] = value;
    }
    size_ = new_size;
}

template <class T, class Allocator>
void Vector<T, Allocator>::reserve(const size_t size) {
    if (size > buffer_size_) {
        resize_buffer(size);
    }
}

template <class T, class Allocator>
size_t Vector<T, Allocator>::size() const {
    return size_;
}

template <class T, class Allocator>
bool Vector<T, Allocator>::empty() const {
    return size_ == 0;
}

template <class T, class Allocator>
void Vector<T, Allocator>::push_back(const T& value) {
    if (size_ == buffer_size_) {
        resize_buffer(buffer_size_ ? buffer_size_ * 2 : 1);
    }

    buffer_[size_] = value;
    size_++;
}

template <class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
    if (size_ == 0) {
        throw std::length_error("container is empty");
    }
    size_--;
}

template <class T, class Allocator>
T& Vector<T, Allocator>::back() {
    if (size_ == 0) {
        throw std::length_error("container is empty");
    }
    return buffer_[size_ - 1];
}

template <class T, class Allocator>
T& Vector<T, Allocator>::operator[](const size_t index) {
    return buffer_[index];
}

template <class T, class Allocator>
const T& Vector<T, Allocator>::operator[](const size_t index) const {
    return buffer_[index];
}


template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin() {
    return buffer_;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cbegin() const {
    return buffer_;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() {
    return buffer_ + size_;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cend() const {
    return buffer_ + size_;
}
