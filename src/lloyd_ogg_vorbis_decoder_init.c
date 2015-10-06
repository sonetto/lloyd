#include <assert.h>
#include <stdio.h>
#include "include/assert_expr.h"

#include "include/lloyd_ogg_vorbis_decoder.h"
#include lloyd_ogg_vorbis_decoder_h(state)
#include lloyd_ogg_vorbis_decoder_h(init_params)

void lloyd_ogg_vorbis_decoder_init(
    lloyd_ogg_vorbis_decoder(state) *state,
    lloyd_ogg_vorbis_decoder(init_params)
) {
    FILE *f = assert_expr(fopen(file_path, "rb"), result != 0);
    assert(ov_open(f, state, 0, 0) == 0);
}
