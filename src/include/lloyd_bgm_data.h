#pragma once

#include "lloyd_buf_count.h"

#include "lloyd_bgm_decoder.h"
#include lloyd_bgm_decoder_h(state)

struct lloyd_source_data;

struct lloyd_bgm_data {
    int allocated;

    struct lloyd_source_data *source;

    unsigned al_bufs[lloyd_buf_count];

    lloyd_bgm_decoder(state) decoder_state;
    int bitrate;

    float fade_in_duration;
    float fade_out_duration;
    int fade_state;
    double fade_start;
};
