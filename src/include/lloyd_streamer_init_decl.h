#include "lloyd_buf.h"
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
