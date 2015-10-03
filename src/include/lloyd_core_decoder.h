#pragma once

#include "lloyd_decoder.h"

#define lloyd_core_use_decoder ogg_vorbis

#include lloyd_decoder_h(core)

#define lloyd_core_decoder lloyd_decoder_of(core)

#define lloyd_core_decoder_init_return_type \
    lloyd_decoder_get(core, init_return_type)

#define lloyd_core_decoder_init_params \
    lloyd_decoder_get(core, init_params)
