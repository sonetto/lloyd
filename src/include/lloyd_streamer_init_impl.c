#include <AL/al.h>
#include "al_safe.h"
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
