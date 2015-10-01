#include <assert.h>
#include <time.h>
#include "include/monotonic_time.h"

double monotonic_time() {
    struct timespec timespec;

    assert(clock_gettime(CLOCK_MONOTONIC, &timespec) == 0);

    return timespec.tv_sec + (timespec.tv_nsec / 1.0e9);
}
