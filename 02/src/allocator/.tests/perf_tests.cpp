#include "allocator/allocator.h"
#include "lib/timer/timer.h"

uint32_t customAllocatorPerfTest(const size_t max_size,
    const size_t allocate_size, const size_t number_of_iterations)
{
    Timer timer;
    Allocator my_alloc(max_size);
    for (size_t i = 0; i < number_of_iterations; i++) {
        void* ptr = my_alloc.allocate(allocate_size);
        if (ptr == nullptr) {
            my_alloc.reset();
            ptr = my_alloc.allocate(allocate_size);
        }
    }
    return timer.get().count();
}

uint32_t mallocPerfTest(const size_t allocate_size, const size_t number_of_iterations) {
    Timer timer;
    for (size_t i = 0; i < number_of_iterations; i++) {
        void* ptr = std::malloc(allocate_size);
        if (ptr != nullptr) {
            free(ptr);
        }
    }
    return timer.get().count();
}

bool runPerfTest(const size_t max_size, const size_t allocate_size,
    const size_t number_of_iterations)
{
    uint32_t custom_allocator_res = customAllocatorPerfTest(max_size,
        allocate_size, number_of_iterations);
    uint32_t malloc_res = mallocPerfTest(allocate_size, number_of_iterations);
    std::cout << "allocator time: " << custom_allocator_res << " us \n";
    std::cout << "malloc time: " << malloc_res << " us \n";
    return custom_allocator_res < malloc_res;
}

int perfTest() {
    int total = 5;
    int success = 0;

    success += runPerfTest(1000, 50, 100000);
    success += runPerfTest(2000, 100, 100000);
    success += runPerfTest(100000, 10000, 100000);
    success += runPerfTest(1000000, 100000, 1000000);
    success += runPerfTest(10000000, 10000000, 1000000);

    std::cout << "total: " << total << "\n";
    std::cout << "success: " << success << "\n";

    return total != success;
}

int main() {
    return perfTest();
}
