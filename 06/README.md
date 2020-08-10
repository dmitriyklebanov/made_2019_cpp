# 06: BigInt

### Task

Write a class for working with large integers. The size of the number is limited only by the size of the memory. We need to support the semantics of working with a regular int:

```c++
BigInt a = 1;
BigInt b = a;
BigInt c = a + b + 2;
```

Implement the operator for output to a stream, addition, subtraction, unary minus, all comparison operations.

std::vector and other containers cannot be used - manage memory yourself.

### Usage

* ```make``` - build BigInt tests
* ```make test``` - launch tests for BigInt
