# 04: Matrix

### Task

You need to write a matrix class, the element type is int. The constructor sets the number of rows and rows. The following operations are supported: get the number of rows / columns, get a specific element, multiply by a number (*=), compare for equality / inequality. In case of an out-of-bounds error, throw an exception:

```c++
throw std::out_of_range("")
```

**Example:**

```c++
const size_t rows = 5;
const size_t cols = 3;

Matrix m(rows, cols);

assert(m.getRows() == 5);
assert(m.getColumns() == 3);

m[1][2] = 5; // строка 1, колонка 2
double x = m[4][1];

m *= 3; // умножение на число

Matrix m1(rows, cols);

if (m1 == m)
{
}
```

##### **Hint:**

In order to implement the semantics \[][] you need a proxy class. The matrix operator returns another class, which also uses the [] operator, and this class already returns a value.

### Usage

* ```make``` - build Matrix tests
* ```make test``` - launch tests for Matrix
