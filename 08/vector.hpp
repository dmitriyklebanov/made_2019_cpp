#pragma once

#include <memory>
#include <stdexcept>

template <class T, class Allocator = std::allocator<T>>
class Vector {
private :
    template <class Pointer, class Reference>
    class IteratorBase;
public :
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = IteratorBase<pointer, reference>;
    using const_iterator = IteratorBase<const_pointer, const_reference>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private :
    size_type buffer_size_ = 0;
    T* buffer_ = nullptr;
    size_type size_ = 0;

    Allocator allocator_ = Allocator();

private :
    T* allocate(const size_type size);
    T* makeCopy(T* from, const size_type size);

    void destroy();
    void resize_buffer(const size_type new_size);

public :
    Vector() = default;
    Vector(const Allocator& allocator);

    Vector(size_type count, const Allocator& allocator = Allocator());
    Vector(size_type count, const T& value, const Allocator& allocator = Allocator());

    Vector(const Vector& obj);
    Vector(Vector&& obj);

    ~Vector();

    Vector& operator =(const Vector& obj);
    Vector& operator =(Vector&& obj);

    void resize(const size_type count);
    void resize(const size_type count, const T& value);

    void reserve(const size_type size);
    size_type capacity() const;

    void clear();

    size_type size() const;
    bool empty() const;

    void push_back(const T& value);
    void push_back(T&& value);

    void pop_back();

    reference back();
    const_reference back() const;

    reference operator[](const size_type index);
    const_reference operator[](const size_type index) const;

    iterator begin();
    const_iterator cbegin() const;

    iterator end();
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator crbegin() const;

    reverse_iterator rend();
    const_reverse_iterator crend() const;
};

template <class T, class Allocator>
template <class Pointer, class Reference>
class Vector<T, Allocator>::IteratorBase : public std::iterator<
    std::random_access_iterator_tag,
    value_type,
    difference_type,
    Pointer,
    Reference>
{
private :
    pointer ptr_;

public :
    IteratorBase(pointer ptr_)
        : ptr_(ptr_)
    {
    }

    IteratorBase& operator ++() {
        ++ptr_;
        return *this;
    }

    IteratorBase operator ++(int) {
        return IteratorBase(ptr_++);
    }

    IteratorBase& operator --() {
        --ptr_;
        return *this;
    }

    IteratorBase operator --(int) {
        return IteratorBase(ptr_--);
    }

    value_type& operator *()  {
        return *ptr_;
    }

    pointer& operator ->() {
        return *ptr_;
    }

    bool operator ==(IteratorBase other) {
        return ptr_ == other.ptr_;
    }

    bool operator !=(IteratorBase other) {
        return !(*this == other);
    }
};

template <class T, class Allocator>
T* Vector<T, Allocator>::allocate(const size_type size) {
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
T* Vector<T, Allocator>::makeCopy(T* from, const size_type size) {
    T* res = allocate(size);
    for (size_type i = 0; i < size; ++i) {
        allocator_.construct(res + i, from[i]);
    }
    return res;
}

template <class T, class Allocator>
void Vector<T, Allocator>::destroy() {
    for (size_type i = 0; i < size_; ++i) {
        buffer_[i].~T();
    }
    if (buffer_ != nullptr) {
        allocator_.deallocate(buffer_, buffer_size_);
        buffer_ = nullptr;
    }
    buffer_size_ = 0;
    size_ = 0;
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize_buffer(const size_type new_buffer_size) {
    T* new_buffer = allocate(new_buffer_size);
    for (size_type i = 0; i < size_; ++i) {
        allocator_.construct(new_buffer + i, buffer_[i]);
    }

    size_t cur_size = size_;
    destroy();

    buffer_size_ = new_buffer_size;
    buffer_ = new_buffer;
    size_ = cur_size;
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(const Allocator& allocator)
    : allocator_(allocator)
{
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count, const Allocator& allocator)
    : buffer_size_(count)
    , buffer_(allocate(count))
    , size_(count)
    , allocator_(allocator)
{
    for (size_type i = 0; i < size_; ++i) {
        allocator_.construct(buffer_ + i);
    }
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count, const T& value, const Allocator& allocator)
    : buffer_size_(count)
    , buffer_(allocate(count))
    , size_(count)
    , allocator_(allocator)
{
    for (size_type i = 0; i < size_; ++i) {
        allocator_.construct(buffer_ + i, value);
    }
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& obj)
    : buffer_size_(obj.size_)
    , buffer_(makeCopy(obj.buffer_, obj.size_))
    , size_(obj.size_)
    , allocator_(obj.allocator_)
{
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
    T* new_buffer = makeCopy(obj.buffer_, obj.size_);
    destroy();
    buffer_size_ = obj.size_;
    buffer_ = new_buffer;
    size_ = obj.size_;
    allocator_ = obj.allocator_;
    return *this;
}

template <class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator =(Vector&& obj) {
    if (this == &obj) {
        return *this;
    }
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
void Vector<T, Allocator>::resize(const size_type count) {
    if (count > buffer_size_) {
        resize_buffer(count);
    }

    if (size_ < count) {
        for (size_type i = size_; i < count; ++i) {
            allocator_.construct(buffer_ + i);
        }
    } else {
        for (size_type i = count; i < size_; ++i) {
            buffer_[i].~T();
        }
    }
    size_ = count;
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize(const size_type count, const T& value) {
    if (count > buffer_size_) {
        resize_buffer(count);
    }

    if (size_ < count) {
        for (size_type i = size_; i < count; ++i) {
            allocator_.construct(buffer_ + i, value);
        }
    } else {
        for (size_type i = count; i < size_; ++i) {
            buffer_[i].~T();
        }
    }
    size_ = count;
}

template <class T, class Allocator>
void Vector<T, Allocator>::reserve(const size_type size) {
    if (size > buffer_size_) {
        resize_buffer(size);
    }
}

template <class T, class Allocator>
typename Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity() const {
    return buffer_size_;
}

template <class T, class Allocator>
void Vector<T, Allocator>::clear() {
    for (size_type i = 0; i < size_; ++i) {
        buffer_[i].~T();
    }
    size_ = 0;
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

    allocator_.construct(buffer_ + size_, value);
    size_++;
}

template <class T, class Allocator>
void Vector<T, Allocator>::push_back(T&& value) {
    if (size_ == buffer_size_) {
        resize_buffer(buffer_size_ ? buffer_size_ * 2 : 1);
    }

    allocator_.construct(buffer_ + size_, std::move(value));
    size_++;
}

template <class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
    if (size_ == 0) {
        throw std::length_error("container is empty");
    }
    buffer_[size_ - 1].~T();
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
typename Vector<T, Allocator>::reference Vector<T, Allocator>::operator[](const size_t index) {
    return buffer_[index];
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::operator[](const size_t index) const {
    return buffer_[index];
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin() {
    return iterator(buffer_);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cbegin() const {
    return const_iterator(buffer_);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() {
    return iterator(buffer_ + size_);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cend() const {
    return const_iterator(buffer_ + size_);
}


template <class T, class Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rbegin() {
    return reverse_iterator(buffer_ + size_);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crbegin() const {
    return const_reverse_iterator(buffer_ + size_);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rend() {
    return reverse_iterator(buffer_);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crend() const {
    return const_reverse_iterator(buffer_);
}
