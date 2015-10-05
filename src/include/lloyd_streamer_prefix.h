#pragma once

#include "cat_double_sandwich.h"

#define lloyd_streamer_prefix(streamer, what) \
    cat_double_sandwich(lloyd_, streamer, _streamer_, what)
