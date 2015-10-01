#include <stdio.h>
#include "src/include/fsleep.h"
#include "src/include/lloyd.h"
#include "src/include/lloyd_bgm.h"

int main() {
    int i = 0;

    lloyd_init();

    lloyd_bgm_set_fade_in_duration(2);
    lloyd_bgm_set_fade_out_duration(2);

    lloyd_bgm_start("bgm0001.ogg");

    while(lloyd_bgm_is_playing()) {
        fsleep(0.01);

        if(++i == 100 * 4) {
            lloyd_bgm_stop();
        }

        lloyd_update();
    }

    lloyd_close();

    return 0;
}
