#include "include/monotonic_time.h"

double monotonic_time_elapsed(double start_time) {
    return monotonic_time() - start_time;
}
