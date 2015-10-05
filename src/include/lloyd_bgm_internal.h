#pragma once

#include "lloyd_buf.h"
#include "lloyd_bgm.h"
#include "lloyd_source_internal.h"

#include lloyd_bgm_streamer(h)(state)

struct lloyd_bgm_data {
    int allocated;

    struct lloyd_source_data *source;

    unsigned al_bufs[lloyd_buf_count];

    lloyd_bgm_streamer(state) streamer_state;

    float fade_in_duration;
    float fade_out_duration;
    int fade_state;
    double fade_start;
};

struct lloyd_bgm_data *lloyd_bgm_alloc();
void lloyd_bgm_free(struct lloyd_bgm_data *bgm);

void lloyd_bgm_update();
void lloyd_bgm_fade_update(struct lloyd_bgm_data *bgm);
void lloyd_bgm_buffers_update(struct lloyd_bgm_data *bgm);

void lloyd_bgm_fade_in(struct lloyd_bgm_data *bgm);
void lloyd_bgm_fade_out(struct lloyd_bgm_data *bgm);
