#include <vorbis/codec.h>
#include "include/assert_expr.h"

#include "include/lloyd_ogg_vorbis_decoder.h"
#include lloyd_ogg_vorbis_decoder_h(state)

int lloyd_ogg_vorbis_decoder_read(
    lloyd_ogg_vorbis_decoder(state) *state,
    void *buf, int len
) {
    int bytes_read = 0;

    while(bytes_read < len) {
        int unused;

        int read_result = assert_expr(ov_read(
            state,
            ((char *)buf) + bytes_read,
            len - bytes_read,
            0, 2, 1, &unused
        ), result >= 0);

        if(read_result == 0) {
            break;
        }

        bytes_read += read_result;
    }

    return bytes_read;
}
