#include <assert.h>
#include <stdio.h>
#include "include/assert_expr.h"
#include "include/lloyd_ogg_vorbis_decoder_internal.h"

#define prefix(s) cat(lloyd_ogg_vorbis_decoder_, s)

prefix(init_return_type)
lloyd_ogg_vorbis_decoder_init(prefix(state) *state, prefix(init_params)) {
    FILE *f = assert_expr(fopen(file_path, "rb"), result != 0);
    assert(ov_open(f, state, 0, 0) == 0);
}
