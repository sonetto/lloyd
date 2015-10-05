#include <AL/al.h>
#include "include/al_safe.h"
#include "include/lloyd_bgm_internal.h"

void lloyd_bgm_buffers_update(struct lloyd_bgm_data *bgm) {
    struct lloyd_source_data *bgm_source = bgm->source;
    lloyd_core_streamer_instance *bgm_streamer_instance = &bgm->streamer_instance;
    int bgm_bitrate = bgm->bitrate;
    unsigned bgm_al_source = bgm_source->al_source;
    int bgm_al_source_state;

    int free_al_buf_count;
    int queued_al_buf_count;

    al_safe(GetSourcei, bgm_al_source, AL_BUFFERS_PROCESSED, &free_al_buf_count);

    while(free_al_buf_count) {
        unsigned free_al_buf;
        char buf[lloyd_buf_len];

        int len_read = lloyd_core_streamer_read(
            bgm_streamer_instance,
            buf, lloyd_buf_len
        );

        if(len_read == lloyd_decoder_eof) {
            break;
        }

        al_safe(SourceUnqueueBuffers, bgm_al_source, 1, &free_al_buf);

        al_safe(
            BufferData, free_al_buf, AL_FORMAT_STEREO16, buf, len_read, bgm_bitrate
        );

        al_safe(SourceQueueBuffers, bgm_al_source, 1, &free_al_buf);

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
