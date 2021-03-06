#pragma once

#include "likely.h"
#include "abort_because.h"

#define al_safe(fn, fn_args...) ({ \
    int _error; \
    \
    al##fn(fn_args); \
    _error = alGetError(); \
    \
    if(unlikely(_error != 0)) { \
        abort_because( \
            "al_safe(" #fn ", " #fn_args ") failed (error code: %d).", _error \
        ); \
    } \
})
