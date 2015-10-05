#pragma once

#include "lloyd_decoder.h"

#define lloyd_streamer_init_return_type(decoder) \
    lloyd_decoder_get(decoder, init_return_type)

#define lloyd_streamer_init_params(decoder) \
    lloyd_decoder_get(decoder, init_params)
