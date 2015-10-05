#include "include/lloyd_ogg_vorbis_decoder_internal.h"

#define prefix(s) cat(lloyd_ogg_vorbis_decoder_, s)

int lloyd_ogg_vorbis_decoder_bitrate(prefix(state) *state) {
    return ov_info(state, -1)->rate;
}
