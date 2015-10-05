#pragma once

#include "cat_double_sandwich.h"

#define lloyd_decoder_prefix(decoder, what) \
    cat_double_sandwich(lloyd_, decoder, _decoder_, what)
