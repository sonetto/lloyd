#pragma once

#include "lloyd_max_sources.h"
#include "lloyd_max_concurrent_bgms.h"
#include "lloyd_source_data.h"
#include "lloyd_bgm_data.h"

struct ALCdevice;
struct ALCcontext;

struct lloyd_context {
    ALCdevice *al_dev;
    ALCcontext *al_ctx;

    struct lloyd_source_data sources[lloyd_max_sources];

    struct lloyd_bgm_data bgms[lloyd_max_concurrent_bgms];
    struct lloyd_bgm_data *bgm;
    float bgm_fade_in_duration;
    float bgm_fade_out_duration;
    int bgm_after_fade_out;
    const char *bgm_next_file_path;
};

extern struct lloyd_context lloyd;
