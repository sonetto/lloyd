#include <stdio.h>
#include "src/include/fsleep.h"
#include "src/include/lloyd.h"
#include "src/include/lloyd_bgm.h"

int main() {
    lloyd_init();

    lloyd_bgm_start("bgm0001.ogg");

    while(lloyd_bgm_is_playing()) {
        fsleep(0.01);
        lloyd_update();
    }

    lloyd_close();

    return 0;
}
