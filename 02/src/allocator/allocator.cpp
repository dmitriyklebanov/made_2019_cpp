#include "allocator.h"

Allocator::Allocator(const size_t size)
    : buffer_(static_cast<char*>(std::malloc(size)))
    , max_size_(size)
{
}

Allocator::~Allocator() {
    if (buffer_) {
        free(buffer_);
    }
}

void* Allocator::allocate(const size_t size) {
    if (buffer_ && size && offset_ + size <= max_size_) {
        void* res_ptr = buffer_ + offset_;
        offset_ += size;
        return res_ptr;
    }

    return nullptr;
}

void Allocator::reset() {
    offset_ = 0;
}

bool Allocator::setMaxSize(const size_t size) {
    if (buffer_ == nullptr) {
        max_size_ = size;
        return true;
    }
    return false;
}

size_t Allocator::getMaxSize() const {
    return max_size_;
}
