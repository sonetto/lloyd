#include "include/monotonic_time.h"
#include "include/lloyd_internal.h"
#include "include/lloyd_fade.h"

void lloyd_bgm_fade_out(struct lloyd_bgm_data *bgm) {
    bgm->fade_out_duration = lloyd.bgm_fade_out_duration;
    bgm->fade_start = monotonic_time();
    bgm->fade_state = lloyd_fade_out;
}
