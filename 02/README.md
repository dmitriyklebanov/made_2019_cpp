# 02: Allocator

### Task

Write your own allocator with a linear memory allocation strategy with the following interface:

```c++
class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
};
```

On creation, the allocator allocates the specified size, after which, when calling alloc, returns a pointer to the block of the requested size or nullptr if there is not enough space. After calling reset, the allocator allows its memory to be used again.

### Usage

* ```make``` - build Allocator and its tests
* ```make test``` - launch tests for Allocator
* ```make perf_test``` - launch perfomance tests for Allocator
