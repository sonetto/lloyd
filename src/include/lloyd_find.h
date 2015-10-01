#pragma once

#define lloyd_find(pool, predicate_expr) ({ \
    int pool_length = sizeof(pool) / sizeof(pool[0]); \
    \
    typeof(pool[0]) *item; \
    typeof(pool[0]) *found = 0; \
    \
    for(int i = 0; i < pool_length; ++i) { \
        item = &pool[i]; \
        \
        if(predicate_expr) { \
            found = item; \
            break; \
        } \
    } \
    \
    found; \
})
