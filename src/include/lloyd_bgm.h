#pragma once

void lloyd_bgm_set_fade_in_duration(float value);

void lloyd_bgm_set_fade_out_duration(float value);

void lloyd_bgm_start(const char *file_path);

void lloyd_bgm_stop();

int lloyd_bgm_is_playing();
