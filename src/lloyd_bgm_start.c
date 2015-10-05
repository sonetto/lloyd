#include "include/al_safe.h"
#include "include/lloyd_internal.h"
#include "include/lloyd_fade.h"
#include "include/lloyd_bgm.h"

#include lloyd_bgm_streamer(h)(init_params)
#include lloyd_bgm_streamer(h)(init)
#include lloyd_bgm_streamer(h)(init_args)

void lloyd_bgm_start(lloyd_bgm_streamer(init_params)) {
    struct lloyd_bgm_data *bgm = lloyd.bgm;
    lloyd_bgm_streamer(state) *bgm_streamer_state;
    struct lloyd_source_data *bgm_source;
    unsigned bgm_al_source;

    if(!bgm) {
        bgm = lloyd.bgm = lloyd_bgm_alloc();
    }

    bgm_streamer_state = &bgm->streamer_state;
    bgm_source = bgm->source;
    bgm_al_source = bgm_source->al_source;

    lloyd_bgm_streamer(init)(
        bgm_streamer_state, bgm_al_source, al_bufs,
        lloyd_bgm_streamer(init_args)
    );

    al_safe(Sourcei, bgm_al_source, AL_LOOPING, 0);

    lloyd_bgm_fade_in(bgm);

    al_safe(Sourcef, bgm_al_source, AL_GAIN, 0);

    al_safe(SourcePlay, bgm_al_source);
}
