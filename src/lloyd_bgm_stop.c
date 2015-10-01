#include "include/lloyd_internal.h"

void lloyd_bgm_stop() {
    struct lloyd_bgm_data *bgm = lloyd.bgm;

    if(!bgm) {
        return;
    }

    lloyd_bgm_fade_out(bgm);
}
