#pragma once

#include <chrono>
#include <iostream>

class Timer {
private :
    using clock_t = std::chrono::high_resolution_clock;

    const clock_t::time_point start_;

public :
    using Milliseconds = std::chrono::microseconds;

    Timer();
    Milliseconds get() const;
};
