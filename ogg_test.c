#include <stdio.h>
#include <unistd.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include "src/include/alc_safe.h"
#include "src/include/al_safe.h"
#include "src/include/assert_expr.h"

static ALCdevice *dev;
static ALCcontext *ctx;

#define buf_count (2)
static unsigned bufs[buf_count];

static unsigned source;

OggVorbis_File ogg_file;
vorbis_info *ogg_info;

static void audio_init() {
    dev = alc_safe(OpenDevice, 0);

    ctx = alc_safe(CreateContext, dev, 0);

    alc_safe(MakeContextCurrent, ctx);

    al_safe(GenBuffers, buf_count, bufs);

    al_safe(GenSources, 1, &source);

    al_safe(Source3i, source, AL_POSITION, 0, 0, -1);

    al_safe(Sourcei, source, AL_SOURCE_RELATIVE, AL_TRUE);

    al_safe(Sourcei, source, AL_ROLLOFF_FACTOR, 0);
}

#define buf_len (1024 * 16)

#define ogg_read_eof (0)
#define ogg_read_ok (1)

static int audio_read_ogg_into_al_buffer(unsigned al_buf) {
    char buf[buf_len];
    int bytes_read = 0;

    while(bytes_read < buf_len) {
        int unused;

        int read_result = assert_expr(
            ov_read(
                &ogg_file,
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
        return ogg_read_eof;
    }

    al_safe(
        BufferData, al_buf, AL_FORMAT_STEREO16, buf, bytes_read, ogg_info->rate
    );


    return ogg_read_ok;
}

static void audio_play_ogg() {
    ALenum source_state;

    assert_expr(
        ov_open_callbacks(stdin, &ogg_file, 0, 0, OV_CALLBACKS_NOCLOSE),
        result == 0
    );

    ogg_info = ov_info(&ogg_file, -1);

    for(int i = 0; i < buf_count; ++i) {
        audio_read_ogg_into_al_buffer(bufs[i]);
    }

    al_safe(SourceQueueBuffers, source, buf_count, bufs);

    al_safe(Sourcei, source, AL_LOOPING, AL_FALSE);

    al_safe(SourcePlay, source);

    while(1) {
        int free_buf_count;
        unsigned free_buf;

        int queued_count;

        usleep(10);

        al_safe(GetSourcei, source, AL_BUFFERS_PROCESSED, &free_buf_count);

        while(free_buf_count) {
            al_safe(SourceUnqueueBuffers, source, 1, &free_buf);

            if(audio_read_ogg_into_al_buffer(free_buf) == ogg_read_ok) {
                al_safe(SourceQueueBuffers, source, 1, &free_buf);
            }

            --free_buf_count;
        }

        al_safe(GetSourcei, source, AL_BUFFERS_QUEUED, &queued_count);

        if(queued_count == 0) {
            break;
        }

        al_safe(GetSourcei, source, AL_SOURCE_STATE, &source_state);

        if(source_state != AL_PLAYING) {
            al_safe(SourcePlay, source);
        }
    }
}

static void audio_close() {
    al_safe(DeleteSources, 1, &source);

    al_safe(DeleteBuffers, buf_count, bufs);

    alc_safe(MakeContextCurrent, 0);

    alc_safe(DestroyContext, ctx);

    alc_safe(CloseDevice, dev);
}

int main() {
    audio_init();

    audio_play_ogg();

    audio_close();

    return 0;
}
