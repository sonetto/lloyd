#include <AL/alc.h>
#include <AL/al.h>
#include "include/alc_safe.h"
#include "include/al_safe.h"
#include "include/lloyd_context.h"
#include "include/lloyd_max_sources.h"
#include "include/lloyd_max_concurrent_bgms.h"
#include "include/lloyd_buf_count.h"

static void al_close() {
    for(int i = 0; i < lloyd_max_sources; ++i) {
        al_safe(DeleteSources, 1, &lloyd.sources[i].al_source);
    }

    for(int i = 0; i < lloyd_max_concurrent_bgms; ++i) {
        al_safe(DeleteBuffers, lloyd_buf_count, lloyd.bgms[i].al_bufs);
    }

    alc_safe(MakeContextCurrent, 0);

    alc_safe(DestroyContext, lloyd.al_ctx);

    alc_safe(CloseDevice, lloyd.al_dev);
}

void lloyd_close() {
    al_close();
}
