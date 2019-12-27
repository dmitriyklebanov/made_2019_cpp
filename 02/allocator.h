#pragma once

#include <cstdlib>

class Allocator {
 private :
    char* buffer_ = nullptr;
    size_t max_size_ = 0;
    size_t offset_ = 0;

 public :
    Allocator() = default;
    explicit Allocator(const size_t size);
    ~Allocator();

    void* allocate(const size_t size);
    void reset();

    bool setMaxSize(const size_t size);
    size_t getMaxSize() const;
};

