#pragma once

#include <chrono>

/**
 * Adapted from C++ High Performance, Bjorn Andrist.
 *
 * "The ScopedTimer class will measure the time from when it was created to the time it went out of
 * scope, that is, destructed" (ANDRIST, Bjorn; C++ High Performance).
 */
class ScopedTimer
{
public:
    using SteadyClock = std::chrono::steady_clock;

    ScopedTimer(const char *function);
    ~ScopedTimer();

    ScopedTimer(const ScopedTimer &) = delete;
    ScopedTimer(ScopedTimer &&) = delete;

    ScopedTimer &operator =(const ScopedTimer &) = delete;
    ScopedTimer &operator =(ScopedTimer &&) = delete;

    void print() const;

private:
    const char *function;
    const SteadyClock::time_point start;
};

