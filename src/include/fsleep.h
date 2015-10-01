#pragma once

#include <unistd.h>

void fsleep(float seconds) {
    usleep(seconds * 1e6);
}
