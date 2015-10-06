#pragma once

#include "cat.h"
#include "cat_sandwich.h"
#include "stringify.h"

#define lloyd_ogg_vorbis_decoder(tail) \
    cat(lloyd_ogg_vorbis_decoder_, tail)

#define lloyd_ogg_vorbis_decoder_h(tail) \
    stringify(cat_sandwich(lloyd_ogg_vorbis_decoder_, tail, .h))
