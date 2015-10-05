#include <AL/al.h>
#include "al_safe.h"
#include "lloyd_buf.h"
#include "lloyd_decoder_internal.h"
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
