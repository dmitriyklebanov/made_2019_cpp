# 09: ThreadPool

### Task

Implement a thread pool with the following interface:

```c++
class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};
```

Using a thread pool:

```c++
struct A {};

void foo(const A&) {}

ThreadPool pool(8);

auto task1 = pool.exec(foo, A());
task1.get();

auto task2 = pool.exec([]() { return 1; });
task2.get();
```

### Usage

* ```make``` - build ThreadPool tests
* ```make test``` - launch tests for ThreadPool
