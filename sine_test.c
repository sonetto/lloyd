#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <AL/al.h>
#include <AL/alc.h>
#include "abort_on_error.h"
#include "pi.h"

static ALCdevice *dev;
static ALCcontext *ctx;

#define buf_count 2
static unsigned bufs[buf_count];

static unsigned source;

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

#define sine_freq 44100
#define sine_buf_len (sine_freq * 4)

static void audio_play_sine() {
    short buf[sine_buf_len];

    ALenum source_state;

    for(int i = 0; i < buf_count; ++i) {
        for(int j = 0; j < sine_buf_len; ++j) {
            buf[j] = (short)(
                sin(j / (float)(sine_freq) * 1000 * 2 * pi / (i + 1)) * 32767
            );
        }

        alBufferData(bufs[i], AL_FORMAT_MONO16, buf, sine_buf_len, sine_freq);
        abort_on_error("alBufferData", alGetError());
    }

    for(int i = 0; i < 2; ++i) {
        alSourceQueueBuffers(source, buf_count, bufs);
        abort_on_error("alSourceQueueBuffers", alGetError());
    }

    alSourcePlay(source);
    abort_on_error("alSourcePlay", alGetError());

    do {
        usleep(10);

        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        abort_on_error("alGetSourcei", alGetError());
    } while(source_state == AL_PLAYING);
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

    audio_play_sine();

    audio_close();

    return 0;
}
