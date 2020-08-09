# 07: format

### Task

Write a function for formatting a string; any type that can be printed to the output stream must be supported. Format string format:

```
"{0} any text {1} {0}"
```

The number in curly braces is the argument number. If there are fewer arguments than the number in parentheses, and in case of other errors, throw std::runtime_error.

Example:

```c++
auto text = format("{1}+{1} = {0}", 2, "one");
assert(text == "one+one = 2");
```

Curly braces are a reserved character, if found out of context {n} throw std::runtime_error

### Usage

* ```make``` - build format tests
* ```make test``` - launch tests for format
