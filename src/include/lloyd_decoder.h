#pragma once

#include "stringify.h"
#include "cat_sandwich.h"
#include "cat_double_sandwich.h"
#include "lloyd_decoder_of.h"

#define lloyd_decoder_h(module) \
    stringify(cat_sandwich(lloyd_, lloyd_decoder_of(module), _decoder.h))

#define lloyd_decoder_get(module, what) \
    cat_double_sandwich(lloyd_, lloyd_decoder_of(module), _decoder_, what)
