#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <AL/al.h>
#include <AL/alc.h>
#include "alc_safe.h"
#include "al_safe.h"
#include "pi.h"

static ALCdevice *dev;
static ALCcontext *ctx;

#define buf_count 2
static unsigned bufs[buf_count];

static unsigned source;

static void audio_init() {
    dev = alc_safe(OpenDevice, NULL);

    ctx = alc_safe(CreateContext, dev, NULL);

    alc_safe(MakeContextCurrent, ctx);

    al_safe(GenBuffers, buf_count, bufs);

    al_safe(GenSources, 1, &source);

    al_safe(Source3i, source, AL_POSITION, 0, 0, -1);

    al_safe(Sourcei, source, AL_SOURCE_RELATIVE, AL_TRUE);

    al_safe(Sourcei, source, AL_ROLLOFF_FACTOR, 0);
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

        al_safe(
            BufferData, bufs[i], AL_FORMAT_MONO16, buf, sine_buf_len, sine_freq
        );
    }

    for(int i = 0; i < 2; ++i) {
        al_safe(SourceQueueBuffers, source, buf_count, bufs);
    }

    al_safe(SourcePlay, source);

    do {
        usleep(10);
        al_safe(GetSourcei, source, AL_SOURCE_STATE, &source_state);
    } while(source_state == AL_PLAYING);
}

static void audio_close() {
    al_safe(DeleteSources, 1, &source);

    al_safe(DeleteBuffers, buf_count, bufs);

    alc_safe(MakeContextCurrent, NULL);

    alc_safe(DestroyContext, ctx);

    alc_safe(CloseDevice, dev);
}

int main(int argc, char **argv) {
    audio_init();

    audio_play_sine();

    audio_close();

    return 0;
}
