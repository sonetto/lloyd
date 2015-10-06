#include "include/lloyd_free.h"
#include "include/lloyd_bgm_data.h"
#include "include/lloyd_source_free.h"

void lloyd_bgm_free(struct lloyd_bgm_data *bgm) {
    lloyd_source_free(bgm->source);
    lloyd_free(bgm);
}
