#include "include/al_safe.h"
#include "include/lloyd_status.h"
#include "include/lloyd_internal.h"
#include "include/lloyd_ogg.h"

void lloyd_bgm_buffers_update(struct lloyd_bgm_data *bgm) {
    struct lloyd_source_data *bgm_source = bgm->source;
    unsigned bgm_al_source = bgm_source->al_source;
    int bgm_al_source_state;

    int free_al_buf_count;
    int queued_al_buf_count;

    al_safe(GetSourcei, bgm_al_source, AL_BUFFERS_PROCESSED, &free_al_buf_count);

    while(free_al_buf_count) {
        unsigned free_al_buf;

        al_safe(SourceUnqueueBuffers, bgm_al_source, 1, &free_al_buf);

        if(lloyd_ogg_read(&bgm->ogg_file, free_al_buf) == lloyd_ok) {
            al_safe(SourceQueueBuffers, bgm_al_source, 1, &free_al_buf);
        }

        --free_al_buf_count;
    }

    al_safe(
        GetSourcei, bgm_al_source, AL_BUFFERS_QUEUED, &queued_al_buf_count
    );

    if(queued_al_buf_count == 0) {
        return;
    }

    al_safe(GetSourcei, bgm_al_source, AL_SOURCE_STATE, &bgm_al_source_state);

    if(bgm_al_source_state != AL_PLAYING) {
        al_safe(SourcePlay, bgm_al_source);
    }
}
