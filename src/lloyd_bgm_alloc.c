#include "include/lloyd_alloc.h"
#include "include/lloyd_source_alloc.h"
#include "include/lloyd_bgm_data.h"

struct lloyd_bgm_data *lloyd_bgm_alloc() {
    struct lloyd_bgm_data *bgm = lloyd_alloc(lloyd.bgms);

    bgm->source = lloyd_source_alloc();

    return bgm;
}
