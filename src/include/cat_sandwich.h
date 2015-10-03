#pragma once

#define cat_sandwich_internal(a, b, c) a##b##c
#define cat_sandwich(a, b, c) cat_sandwich_internal(a, b, c)
