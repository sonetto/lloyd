#pragma once

#include "lloyd_core_streamer.h"

void lloyd_bgm_set_fade_in_duration(float value);

void lloyd_bgm_set_fade_out_duration(float value);

lloyd_core_streamer_init_return_type
lloyd_bgm_start(lloyd_core_streamer_init_params);

void lloyd_bgm_stop();

int lloyd_bgm_is_playing();
