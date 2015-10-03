#pragma once

#include "cat_sandwich.h"
#include "cat_double_sandwich.h"
#include "lloyd_decoder_of.h"

#define lloyd_decoder_internal_h(module) \
    stringify(cat_sandwich(lloyd_, lloyd_decoder_of(module), _decoder_internal.h))

#define lloyd_decoder(module, fn, args...) \
    (cat_double_sandwich(lloyd_, lloyd_decoder_of(module), _decoder_, fn)(args))

#define lloyd_decoder_eof (0)
