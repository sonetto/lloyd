#include "lloyd_ogg_vorbis_decoder.h"

#include lloyd_ogg_vorbis_decoder_h(state)

int lloyd_ogg_vorbis_decoder_bitrate(
    lloyd_ogg_vorbis_decoder(state) *state
) {
    return ov_info(state, -1)->rate;
}
