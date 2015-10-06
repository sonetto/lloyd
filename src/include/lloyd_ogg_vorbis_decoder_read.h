#pragma once

#include "lloyd_ogg_vorbis_decoder.h"

#include lloyd_ogg_vorbis_decoder_h(state)

int lloyd_ogg_vorbis_decoder_read(
    prefix(state) *state,
    void *buf, int len
);
