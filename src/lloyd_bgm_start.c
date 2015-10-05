#include "include/al_safe.h"
#include "include/lloyd_internal.h"
#include "include/lloyd_fade.h"
#include "include/lloyd_bgm.h"

lloyd_core_streamer_init_return_type
lloyd_bgm_start(lloyd_core_streamer_init_params) {
    struct lloyd_bgm_data *bgm = lloyd.bgm;
    lloyd_core_streamer_instance *bgm_streamer_instance;
    int bgm_bitrate;
    struct lloyd_source_data *bgm_source;
    unsigned bgm_al_source;
    int bgm_al_source_queued_bufs;

    if(!bgm) {
        bgm = lloyd.bgm = lloyd_bgm_alloc();
    }

    bgm_streamer_instance = &bgm->streamer_instance;
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

    lloyd_core_streamer_init(bgm_streamer_instance, lloyd_core_streamer_init_args);

    bgm_bitrate = bgm->bitrate = lloyd_core_streamer_bitrate(bgm_streamer_instance);

    for(int i = 0; i < lloyd_buf_count; ++i) {
        char buf[lloyd_buf_len];
        unsigned al_buf = bgm->al_bufs[i];

        int len_read = lloyd_core_streamer_read(
            bgm_streamer_instance,
            buf, lloyd_buf_len
        );

        if(len_read == lloyd_decoder_eof) {
            break;
        }

        al_safe(BufferData, al_buf, AL_FORMAT_STEREO16, buf, len_read, bgm_bitrate);

        al_safe(SourceQueueBuffers, bgm_al_source, 1, &al_buf);
    }

    al_safe(Sourcei, bgm_al_source, AL_LOOPING, 0);

    lloyd_bgm_fade_in(bgm);

    al_safe(Sourcef, bgm_al_source, AL_GAIN, 0);

    al_safe(SourcePlay, bgm_al_source);
}
