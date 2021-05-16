#include "ScopedTimer.h"

#include <iostream>

using namespace std::chrono;

ScopedTimer::ScopedTimer(const char *function)
    : function(function)
    , start(SteadyClock::now())
{

}

void ScopedTimer::print() const
{
    const auto stop = SteadyClock::now();
    const auto duration = stop - start;
    const auto ms = duration_cast<milliseconds>(duration).count();

    std::cout << ms << " ms " << function << "\n";
}

ScopedTimer::~ScopedTimer()
{
    print();
}
