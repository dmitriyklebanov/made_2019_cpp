#include <functional>

#include "allocator/allocator.h"
#include "lib/tester.hpp"

int test() {
    using TestFunc = std::function<bool(const size_t, const size_t, const size_t, size_t)>;
    TestFunc test_func =
        [](const size_t max_size, const size_t allocate_size,
            const size_t number_of_iterations, size_t number_of_resets)
        {
            number_of_resets--;
            Allocator my_alloc(max_size);
            for (size_t i = 0; i < number_of_iterations; i++) {
                void* ptr = my_alloc.allocate(allocate_size);
                if (ptr == nullptr) {
                    my_alloc.reset();
                    number_of_resets--;
                }
            }
            return number_of_resets == 0;
        };
    Tester<TestFunc> allocator_tester(test_func);

    allocator_tester.execute(5, 1, 3, 1);
    allocator_tester.execute(5, 2, 3, 2);
    allocator_tester.execute(5, 5, 4, 3);
    allocator_tester.execute(5, 0, 1, 2);
    allocator_tester.execute(16, 2, 64, 8);

    allocator_tester.printStatistics();
    return allocator_tester.getTotal() != allocator_tester.getSuccess();
}

int main() {
    return test();
}
