#pragma once

#include "lloyd_ogg_vorbis_decoder.h"

#include lloyd_ogg_vorbis_decoder_h(state)
#include lloyd_ogg_vorbis_decoder_h(init_params)

void lloyd_ogg_vorbis_decoder_init(
    lloyd_ogg_vorbis_decoder(state) *state,
    lloyd_ogg_vorbis_decoder(init_params)
);
