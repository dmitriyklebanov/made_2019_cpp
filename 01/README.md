# 01: Calculator

### Task

Using the recursive descent method, write a calculator. Supported operations:

- multiplication
- division
- addition
- subtraction
- unary minus

For calculations, use the int type, the priority of operations is standard. The expression is passed through the command line argument, the supplied numbers are integers, the result is output to cout. Example:

```
calc "2 + 3 * 4 - -2"
```

Output:

```
16
```

There should be error handling, in case of an incorrect expression, output an error to the console and return a code other than 0. Tests are required.

### Usage

* ```make``` - build Calculator and its tests
* ```make run ARGS="expr"``` - launch Calculator with expression "expr"
* ```make test``` - launch tests for Calculator
