#pragma once

#include "assert_expr.h"
#include "lloyd_find.h"

#define lloyd_alloc(pool) ({ \
    typeof(pool[0]) *item = assert_expr( \
        lloyd_find(pool, !item->allocated), result != 0 \
    ); \
    \
    item->allocated = 1; \
    \
    item; \
})
