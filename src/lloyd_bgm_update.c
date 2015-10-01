#include "include/al_safe.h"
#include "include/lloyd_internal.h"

void lloyd_bgm_update() {
    struct lloyd_bgm_data *bgm;

    for(int i = 0; i < lloyd_max_concurrent_bgms; ++i) {
        struct lloyd_source_data *bgm_source;
        unsigned bgm_al_source;
        int bgm_al_source_queued_bufs;

        bgm = &lloyd.bgms[i];

        if(!bgm->allocated) {
            continue;
        }

        bgm_source = bgm->source;
        bgm_al_source = bgm_source->al_source;

        lloyd_bgm_buffers_update(bgm);

        lloyd_bgm_fade_update(bgm);

        al_safe(
            GetSourcei, bgm_al_source, AL_BUFFERS_QUEUED, &bgm_al_source_queued_bufs
        );

        if(bgm_al_source_queued_bufs == 0) {
            lloyd_bgm_free(bgm);
            lloyd.bgm = 0;
        }
    }
}
