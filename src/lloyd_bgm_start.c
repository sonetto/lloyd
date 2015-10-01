#include "include/al_safe.h"
#include "include/lloyd_internal.h"
#include "include/lloyd_fade.h"
#include "include/lloyd_ogg.h"

void lloyd_bgm_start(const char *file_path) {
    struct lloyd_bgm_data *bgm = lloyd.bgm;
    struct lloyd_source_data *bgm_source;
    unsigned bgm_al_source;
    int bgm_al_source_queued_bufs;

    if(!bgm) {
        bgm = lloyd.bgm = lloyd_bgm_alloc();
    }

    bgm_source = bgm->source;
    bgm_al_source = bgm_source->al_source;

    al_safe(GetSourcei, bgm_al_source, AL_BUFFERS_QUEUED, &bgm_al_source_queued_bufs);

    if(bgm_al_source_queued_bufs > 0) {
        lloyd_bgm_stop();
        lloyd.bgm = 0;

        lloyd.bgm_next_file_path = file_path;
        lloyd.bgm_after_fade_out = lloyd_bgm_after_fade_out_start_next;

        return;
    }

    lloyd_ogg_open(file_path, &bgm->ogg_file);

    for(int i = 0; i < lloyd_buf_count; ++i) {
        unsigned al_buf = bgm->al_bufs[i];

        if(lloyd_ogg_read(&bgm->ogg_file, al_buf) == lloyd_ogg_eof) {
            break;
        }

        al_safe(SourceQueueBuffers, bgm_al_source, 1, &al_buf);
    }

    al_safe(Sourcei, bgm_al_source, AL_LOOPING, 0);

    lloyd_bgm_fade_in(bgm);

    al_safe(Sourcef, bgm_al_source, AL_GAIN, 0);

    al_safe(SourcePlay, bgm_al_source);
}
