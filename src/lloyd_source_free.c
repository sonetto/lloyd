#include <assert.h>
#include <AL/al.h>
#include "include/al_safe.h"
#include "include/lloyd_free.h"
#include "include/lloyd_source_data.h"
#include "include/lloyd_buf_count.h"

void lloyd_source_free(struct lloyd_source_data *source) {
    unsigned bgm_al_source = source->al_source;
    int bgm_al_source_free_al_bufs;

    unsigned free_al_bufs[lloyd_buf_count];

    al_safe(SourceStop, bgm_al_source);

    al_safe(
        GetSourcei, bgm_al_source,
        AL_BUFFERS_PROCESSED, &bgm_al_source_free_al_bufs
    );

    assert(bgm_al_source_free_al_bufs <= lloyd_buf_count);

    al_safe(
        SourceUnqueueBuffers, bgm_al_source, bgm_al_source_free_al_bufs, free_al_bufs
    );

    lloyd_free(source);
}
