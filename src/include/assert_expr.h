#pragma once

#include "abort_because.h"

#define assert_expr(expr, assertion) ({ \
    typeof(expr) result = expr; \
    \
    if(!(assertion)) { \
        abort_because( \
            "assert_expr(" #expr ", " #assertion ") failed (result == %d).", \
            result \
        ); \
    } \
    \
    result; \
})
