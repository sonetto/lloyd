#include <AL/al.h>
#include "include/al_safe.h"
#include "include/lloyd_context.h"
#include "include/lloyd_bgm_alloc.h"
#include "include/lloyd_source_data.h"
#include "include/lloyd_bgm_stop.h"
#include "include/lloyd_buf_count.h"
#include "include/lloyd_bgm_after_fade_out_action.h"
#include "include/lloyd_decoder_eof.h"
#include "include/lloyd_bgm_fade_in.h"

#include "include/lloyd_bgm_decoder.h"
#include lloyd_bgm_decoder_h(init_params)
#include lloyd_bgm_decoder_h(state)
#include lloyd_bgm_decoder_h(init)
#include lloyd_bgm_decoder_h(bitrate)

void lloyd_bgm_start(lloyd_bgm_decoder(init_params)) {
    struct lloyd_bgm_data *bgm = lloyd.bgm;
    lloyd_bgm_decoder(state) *bgm_decoder_state;
    int bgm_bitrate;
    struct lloyd_source_data *bgm_source;
    unsigned bgm_al_source;
    int bgm_al_source_queued_bufs;

    if(!bgm) {
        bgm = lloyd.bgm = lloyd_bgm_alloc();
    }

    bgm_decoder_state = &bgm->decoder_state;
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

    lloyd_bgm_decoder(init)(bgm_decoder_state, lloyd_bgm_decoder(init_args));

    bgm_bitrate = bgm->bitrate = lloyd_bgm_decoder(bitrate)(bgm_decoder_state);

    for(int i = 0; i < lloyd_buf_count; ++i) {
        char buf[lloyd_buf_len];
        unsigned al_buf = bgm->al_bufs[i];

        int len_read = lloyd_bgm_decoder(read)(
            bgm_decoder_state, buf, lloyd_buf_len
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
