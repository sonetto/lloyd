// lloyd_decoder_prefix.h

// lloyd_streamer_prefix.h

// lloyd_streamer_read_to_al_decl.h

// lloyd_streamer_read_to_al_impl.c
#include "lloyd_streamer_read_to_al_decl.h"

lloyd_streamer_read_to_al_decl(streamer) {
    lloyd_decoder_prefix(decoder, state) *decoder_state = (
        &streamer_state->decoder_state
    );

    char buf[lloyd_buf_len];

    int read_result = lloyd_decoder_prefix(decoder, read)(
        decoder_state, buf, lloyd_buf_len
    );

    if(read_result == lloyd_decoder_eof) {
        return 0;
    }

    al_safe(
        BufferData, al_buf, AL_FORMAT_STEREO16,
        buf, read_result, streamer_state->bitrate
    );

    return 1;
}

// lloyd_streamer_init_decl.h
#include "lloyd_decoder_prefix.h"
#include "lloyd_streamer_prefix.h"

#define lloyd_streamer_init_return_type(decoder) \
    lloyd_decoder_prefix(decoder, init_return_type)

#define lloyd_streamer_init_params(decoder) \
    unsigned al_bufs[lloyd_buf_count], unsigned al_source, \
    lloyd_decoder_prefix(decoder, init_params)

#define lloyd_streamer_init_decl(streamer) \
    lloyd_streamer_init_return_type \
    lloyd_streamer_prefix(streamer, init)( \
        lloyd_streamer_prefix(streamer, state) *streamer_state, \
        lloyd_streamer_prefix(streamer, init_params) \
    )

// lloyd_streamer_init_impl.c
#include "lloyd_streamer_init_decl.h"

lloyd_streamer_init_decl(streamer) {
    lloyd_decoder_prefix(decoder, state) *decoder_state = (
        &streamer_state->decoder_state;
    );

    lloyd_decoder_prefix(decoder, init)(
        decoder_state, lloyd_decoder_prefix(decoder, init_args)
    );

    streamer_state->bitrate = (
        lloyd_decoder_prefix(decoder, bitrate)(decoder_state);
    );

    for(int i = 0; i < lloyd_buf_count; ++i) {
        unsigned al_buf = al_bufs[i];

        if(!lloyd_streamer_prefix(streamer, read_to_al)(streamer_state, al_buf)) {
            break;
        }

        al_safe(SourceQueueBuffers, 1, &al_buf);
    }
}

// lloyd_streamer_update_decl.h
#include "lloyd_streamer_prefix.h"

#define lloyd_streamer_update_decl(streamer) \
    int lloyd_streamer_prefix(streamer, update)(unsigned al_source)

// lloyd_streamer_update_impl.c
#include "lloyd_streamer_update_decl.h"

lloyd_streamer_update_decl(streamer) {
    int free_al_buf_count;

    al_safe(GetSourcei, al_source, AL_BUFFERS_PROCESSED, &free_al_buf_count);

    while(free_al_buf_count--) {
        unsigned al_buf;

        al_safe(SourceUnqueueBuffers, al_source, 1, &al_buf);

        if(!lloyd_streamer_prefix(streamer, read_to_al)(streamer_state, al_buf)) {
            break;
        }

        al_safe(SourceQueueBuffers, al_source, 1, &al_buf);
    }

    int queued_al_buf_count;

    al_safe(GetSourcei, al_source, AL_BUFFERS_QUEUED, &queued_al_buf_count);

    if(queued_al_buf_count == 0) {
        return;
    }

    al_safe(GetSourcei, al_source, AL_SOURCE_STATE, &al_source_state);

    if(al_source_state != AL_PLAYING) {
        al_safe(SourcePlay, al_source);
    }
}
