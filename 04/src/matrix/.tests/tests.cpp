#include <functional>

#include "lib/tester.hpp"
#include "matrix/matrix.h"

int test() {
    using TestFunc = std::function<bool(const Matrix&, const size_t,
        const size_t, const int, const bool)>;
    TestFunc test_func = [](
        const Matrix& matrix,
        const size_t i,
        const size_t j,
        const int ans,
        const bool thrown_exception)
        {
            int res = 0;
            try {
                res = matrix[i][j];
            } catch (...) {
                return thrown_exception;
            }
            return res == ans;
        };
    Tester<TestFunc> matrix_tester(test_func);

    Matrix matrix = {
        {1, 2, 3},
        {-1, 0, 1}
    };
    matrix *= -3;

    matrix_tester.execute(matrix, 0, 0, -3, false);
    matrix_tester.execute(matrix, 0, 1, -6, false);
    matrix_tester.execute(matrix, 0, 2, -9, false);
    matrix_tester.execute(matrix, 1, 0, 3, false);
    matrix_tester.execute(matrix, 1, 1, 0, false);
    matrix_tester.execute(matrix, 1, 2, -3, false);
    matrix_tester.execute(matrix, 1, 3, 0, true);
    matrix_tester.execute(matrix, 2, 2, 0, true);

    matrix_tester.printStatistics();
    std::cout << "Test matrix:\n";
    for (const auto& row : matrix) {
        for (const auto& item : row) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Number of rows: " << matrix.getRowsSize() << "\n";
    std::cout << "Number of columns: " << matrix.getColumnsSize() << "\n";

    return matrix_tester.getTotal() != matrix_tester.getSuccess();
}

int main() {
    return test();
}
