#pragma once

#include "lloyd_bgm_streamer.h"

#include lloyd_bgm_streamer(h)(init_params)

void lloyd_bgm_set_fade_in_duration(float value);

void lloyd_bgm_set_fade_out_duration(float value);

void lloyd_bgm_start(lloyd_bgm_streamer(init_params));

void lloyd_bgm_stop();

int lloyd_bgm_is_playing();
