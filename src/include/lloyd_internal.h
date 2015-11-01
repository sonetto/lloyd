#pragma once

#include <AL/alc.h>
#include <AL/al.h>
#include "lloyd.h"
#include "lloyd_max_path_len.h"
#include "lloyd_source_internal.h"
#include "lloyd_bgm_internal.h"

#define lloyd_max_sources (32)

#define lloyd_max_concurrent_bgms (2)

struct lloyd_context {
    ALCdevice *al_dev;
    ALCcontext *al_ctx;

    struct lloyd_source_data sources[lloyd_max_sources];

    struct lloyd_bgm_data bgms[lloyd_max_concurrent_bgms];
    struct lloyd_bgm_data *bgm;
    float bgm_fade_in_duration;
    float bgm_fade_out_duration;
    int bgm_after_fade_out;
    char bgm_next_file_path[lloyd_max_path_len];
};

extern struct lloyd_context lloyd;
