#pragma once

#define cat_double_sandwich_internal(a, b, c, d) a##b##c##d
#define cat_double_sandwich(a, b, c, d) cat_double_sandwich_internal(a, b, c, d)
