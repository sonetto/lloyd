#include <AL/al.h>
#include "include/al_safe.h"
#include "include/lloyd_max_concurrent_bgms.h"
#include "include/lloyd_context.h"
#include "include/lloyd_bgm_data.h"
#include "include/lloyd_source_data.h"

int lloyd_bgm_is_playing() {
    for(int i = 0; i < lloyd_max_concurrent_bgms; ++i) {
        struct lloyd_bgm_data *bgm;
        struct lloyd_source_data *bgm_source;
        unsigned bgm_al_source;
        int bgm_al_source_queued_bufs;

        bgm = &lloyd.bgms[i];

        if(!bgm->allocated) {
            continue;
        }

        bgm_source = bgm->source;
        bgm_al_source = bgm_source->al_source;

        al_safe(
            GetSourcei, bgm_al_source,
            AL_BUFFERS_QUEUED, &bgm_al_source_queued_bufs
        );

        if(bgm_al_source_queued_bufs > 0) {
            return 1;
        }
    }

    return 0;
}
