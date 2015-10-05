#pragma once

#include "cat.h"
#include "stringify.h"

#define lloyd_core_streamer(tail) cat(lloyd_core_streamer_, tail)

#define lloyd_core_streamer_h(tail) \
    stringify(cat_sandwich(lloyd_core_streamer_, tail, .h))
