#include <assert.h>
#include <stdio.h>
#include "include/assert_expr.h"
#include "include/lloyd_ogg.h"

void lloyd_ogg_open(const char *file_path, OggVorbis_File *ogg_file) {
    FILE *f = assert_expr(fopen(file_path, "rb"), result != 0);
    assert(ov_open(f, ogg_file, 0, 0) == 0);
}
