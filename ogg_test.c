#include <stdio.h>
#include <unistd.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include "common.h"

static ALCdevice *dev;
static ALCcontext *ctx;

#define buf_count (2)
static unsigned bufs[buf_count];

static unsigned source;

OggVorbis_File ogg_file;
vorbis_info *ogg_info;

static void audio_init() {
    dev = alcOpenDevice(NULL);
    abort_on_error("alcOpenDevice", alcGetError(dev));

    ctx = alcCreateContext(dev, NULL);
    abort_on_error("alcCreateContext", alcGetError(dev));

    alcMakeContextCurrent(ctx);
    abort_on_error("alcMakeContextCurrent", alcGetError(dev));

    alGenBuffers(buf_count, bufs);
    abort_on_error("alGenBuffers", alGetError());

    alGenSources(1, &source);
    abort_on_error("alGenSources", alGetError());

    alSource3i(source, AL_POSITION, 0, 0, -1);
    abort_on_error("alSource3i", alGetError());

    alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
    abort_on_error("alSourcei", alGetError());

    alSourcei(source, AL_ROLLOFF_FACTOR, 0);
    abort_on_error("alSourcei", alGetError());
}

#define buf_len (1024 * 16)

#define ogg_read_eof (0)
#define ogg_read_ok (1)

static int audio_read_ogg_into_al_buffer(unsigned al_buf) {
    char buf[buf_len];
    int bytes_read = 0;

    while(bytes_read < buf_len) {
        int unused;

        int read_result = ov_read(
            &ogg_file, buf + bytes_read, sizeof(buf) - bytes_read, 0, 2, 1, &unused
        );

        if(read_result < 0) {
            abort_on_error("ov_read", read_result);
        }
        else
        if(read_result == 0) {
            break;
        }

        bytes_read += read_result;
    }

    if(bytes_read == 0) {
        return ogg_read_eof;
    }

    alBufferData(
        al_buf, AL_FORMAT_STEREO16, buf, bytes_read, ogg_info->rate
    );

    abort_on_error("alBufferData", alGetError());

    return ogg_read_ok;
}

static void audio_play_ogg() {
    ALenum source_state;

    abort_on_error(
        "ov_open_callbacks",
        ov_open_callbacks(stdin, &ogg_file, NULL, 0, OV_CALLBACKS_NOCLOSE)
    );

    ogg_info = ov_info(&ogg_file, -1);

    for(int i = 0; i < buf_count; ++i) {
        audio_read_ogg_into_al_buffer(bufs[i]);
    }

    alSourceQueueBuffers(source, buf_count, bufs);
    abort_on_error("alSourceQueueBuffers", alGetError());

    alSourcei(source, AL_LOOPING, AL_FALSE);
    abort_on_error("alSourcei", alGetError());

    alSourcePlay(source);
    abort_on_error("alSourcePlay", alGetError());

    while(1) {
        int free_buf_count;
        unsigned free_buf;

        int queued_count;

        usleep(10);

        alGetSourcei(source, AL_BUFFERS_PROCESSED, &free_buf_count);
        abort_on_error("alGetSourcei", alGetError());

        while(free_buf_count) {
            alSourceUnqueueBuffers(source, 1, &free_buf);
            abort_on_error("alSourceUnqueueBuffers", alGetError());

            if(audio_read_ogg_into_al_buffer(free_buf) == ogg_read_ok) {
                alSourceQueueBuffers(source, 1, &free_buf);
                abort_on_error("alSourceQueueBuffers", alGetError());
            }

            --free_buf_count;
        }

        alGetSourcei(source, AL_BUFFERS_QUEUED, &queued_count);
        abort_on_error("alGetSourcei", alGetError());

        if(queued_count == 0) {
            break;
        }

        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        abort_on_error("alGetSourcei", alGetError());

        if(source_state != AL_PLAYING) {
            alSourcePlay(source);
            abort_on_error("alSourcePlay", alGetError());
        }
    }
}

static void audio_close() {
    alDeleteSources(1, &source);
    abort_on_error("alDeleteSources", alGetError());

    alDeleteBuffers(buf_count, bufs);
    abort_on_error("alDeleteBuffers", alGetError());

    alcMakeContextCurrent(NULL);
    abort_on_error("alcMakeContextCurrent", alcGetError(dev));

    alcDestroyContext(ctx);
    abort_on_error("alcDestroyContext", alcGetError(dev));

    alcCloseDevice(dev);
    abort_on_error("alcCloseDevice", alcGetError(dev));
}

int main(int argc, char **argv) {
    audio_init();

    audio_play_ogg();

    audio_close();

    return 0;
}
