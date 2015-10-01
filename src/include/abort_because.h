#pragma once

#include <stdlib.h>

#define abort_because(message, more...) ({ \
    fprintf( \
        stderr, \
        __FILE__ ":%d: " message "\n", \
        __LINE__, \
        ##more \
    ); \
    \
    exit(-1); \
})
