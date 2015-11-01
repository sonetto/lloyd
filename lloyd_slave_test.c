#include "src/include/fsleep.h"
#include "src/include/lloyd.h"
#include "build/libslave/libslave.h"

int main() {
    lloyd_init();

    while(!slave_dismissed()) {
        fsleep(0.01);

        slave_update();

        lloyd_update();
    }

    lloyd_close();

    return 0;
}
