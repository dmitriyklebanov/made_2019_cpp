# 08: Vector

### Task

Write your own Vector container similar to std::vector, allocator and random access iterator for it. Of the supported methods, operator [], push_back, pop_back, empty, size, clear, begin, end, rbegin, rend, resize, reserve are sufficient.

For the tests to pass, the classes must have the following names:

```c++
template <class T>
class Allocator
{
};

template <class T>
class Iterator
{
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;

private:
    Alloc alloc_;
};
```

See the documentation for the interface of the allocator and iterator.

### Usage

* ```make``` - build Vector tests
* ```make test``` - launch tests for Vector
