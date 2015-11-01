#include <math.h>
#include <stdio.h>
#include "include/clamp.h"
#include "include/monotonic_time.h"
#include "include/al_safe.h"
#include "include/lloyd_internal.h"
#include "include/lloyd_fade.h"

static float lloyd_compute_fade_out_gain(float duration, float elapsed) {
    return clamp((duration - elapsed) / duration, 0, 1);
}

static void lloyd_bgm_fade_in_update(struct lloyd_bgm_data *bgm) {
    struct lloyd_source_data *bgm_source = bgm->source;
    unsigned bgm_al_source = bgm_source->al_source;

    float seconds_elapsed = monotonic_time_elapsed(bgm->fade_start);

    float bgm_gain = 1 - lloyd_compute_fade_out_gain(
        bgm->fade_in_duration, seconds_elapsed
    );

    al_safe(Sourcef, bgm_al_source, AL_GAIN, bgm_gain);

    if(bgm_gain >= 1) {
        bgm->fade_state = lloyd_fade_none;
    }
}

static void lloyd_bgm_start_next() {
    lloyd_bgm_start(lloyd.bgm_next_file_path);

    lloyd.bgm_next_file_path[0] = 0;
    lloyd.bgm_after_fade_out = 0;
}

static void lloyd_bgm_after_fade_out() {
    switch(lloyd.bgm_after_fade_out) {
        case 0:
            lloyd_bgm_free(lloyd.bgm);
            break;
        case lloyd_bgm_after_fade_out_start_next:
            lloyd_bgm_start_next();
            break;
    }
}

static void lloyd_bgm_fade_out_update(struct lloyd_bgm_data *bgm) {
    struct lloyd_source_data *bgm_source = bgm->source;
    unsigned bgm_al_source = bgm_source->al_source;

    float seconds_elapsed = monotonic_time_elapsed(bgm->fade_start);

    float bgm_gain = lloyd_compute_fade_out_gain(
        bgm->fade_out_duration, seconds_elapsed
    );

    al_safe(Sourcef, bgm_al_source, AL_GAIN, bgm_gain);

    if(bgm_gain <= 0) {
        bgm->fade_state = lloyd_fade_none;
        lloyd_bgm_free(bgm);
        lloyd_bgm_after_fade_out();
    }
}

void lloyd_bgm_fade_update(struct lloyd_bgm_data *bgm) {
    switch(bgm->fade_state) {
        case lloyd_fade_in:
            lloyd_bgm_fade_in_update(bgm);
            break;

        case lloyd_fade_out:
            lloyd_bgm_fade_out_update(bgm);
            break;
    }
}
