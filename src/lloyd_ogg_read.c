#include <AL/al.h>
#include <vorbis/codec.h>
#include "include/assert_expr.h"
#include "include/al_safe.h"
#include "include/lloyd_status.h"
#include "include/lloyd_buf.h"
#include "include/lloyd_ogg.h"

int lloyd_ogg_read(OggVorbis_File *ogg_file, unsigned al_buf) {
    vorbis_info *ogg_info = ov_info(ogg_file, -1);

    static char buf[lloyd_buf_len];
    int bytes_read = 0;

    while(bytes_read < lloyd_buf_len) {
        int unused;

        int read_result = assert_expr(
            ov_read(
                ogg_file,
                buf + bytes_read,
                sizeof(buf) - bytes_read,
                0, 2, 1, &unused
            ),
            result >= 0
        );

        if(read_result == 0) {
            break;
        }

        bytes_read += read_result;
    }

    if(bytes_read == 0) {
        return lloyd_ogg_eof;
    }

    al_safe(
        BufferData, al_buf, AL_FORMAT_STEREO16, buf, bytes_read, ogg_info->rate
    );

    return lloyd_ok;
}
