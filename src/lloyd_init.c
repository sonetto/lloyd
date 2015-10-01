#include "include/alc_safe.h"
#include "include/al_safe.h"
#include "include/lloyd.h"
#include "include/lloyd_internal.h"

static void al_init() {
    lloyd.al_dev = alc_safe(OpenDevice, 0);

    lloyd.al_ctx = alc_safe(CreateContext, lloyd.al_dev, 0);

    alc_safe(MakeContextCurrent, lloyd.al_ctx);

    for(int i = 0; i < lloyd_max_concurrent_bgms; ++i) {
        al_safe(GenBuffers, lloyd_buf_count, lloyd.bgms[i].al_bufs);
    }

    for(int i = 0; i < lloyd_max_sources; ++i) {
        unsigned al_source;

        al_safe(GenSources, 1, &al_source);

        al_safe(Source3i, al_source, AL_POSITION, 0, 0, -1);

        al_safe(Sourcei, al_source, AL_SOURCE_RELATIVE, AL_TRUE);

        al_safe(Sourcei, al_source, AL_ROLLOFF_FACTOR, 0);

        lloyd.sources[i].al_source = al_source;
    }
}

void lloyd_init() {
    al_init();
}
