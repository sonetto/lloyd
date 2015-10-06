#pragma once

#include "unlikely.h"
#include "abort_because.h"

#define alc_safe_abort_on_error(fn, fn_args...) \
    if(unlikely(_error != 0)) { \
        abort_because( \
            "alc" #fn "(" #fn_args ") failed (error code: %d).", _error \
        ); \
    }

#define alc_safe_default(fn, fn_args...) ({ \
    int _error; \
    \
    typeof(alc##fn(fn_args)) result = alc##fn(fn_args); \
    _error = alcGetError(0); \
    \
    alc_safe_abort_on_error(fn, fn_args); \
    \
    result; \
})

#define alc_safe_default_void(fn, fn_args...) ({ \
    int _error; \
    \
    alc##fn(fn_args); \
    _error = alcGetError(0); \
    \
    alc_safe_abort_on_error(fn, fn_args); \
})

#define alc_safe_OpenDevice(args...) \
    (alc_safe_default(OpenDevice, args))

#define alc_safe_CreateContext(dev, args...) ({ \
    int _error; \
    \
    typeof(alcCreateContext(dev, args)) result = alcCreateContext(dev, args); \
    _error = alcGetError(dev); \
    \
    alc_safe_abort_on_error(CreateContext, dev, fn_args); \
    \
    result; \
})

#define alc_safe_MakeContextCurrent(args...) \
    (alc_safe_default(MakeContextCurrent, args))

#define alc_safe_DestroyContext(args...) \
    (alc_safe_default_void(DestroyContext, args))

#define alc_safe_CloseDevice(args...) \
    (alc_safe_default(CloseDevice, args))

#define alc_safe(fn, fn_args...) (alc_safe_##fn(fn_args))
