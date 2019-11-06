#include "timer.h"

Timer::Timer()
    : start_(clock_t::now())
{
}

Timer::Milliseconds Timer::get() const {
    const auto finish = clock_t::now();
    return std::chrono::duration_cast<Milliseconds>(finish - start_);
}
