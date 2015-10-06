#pragma once

#define lloyd_cat_internal(a, b) lloyd_##a##_##b
#define lloyd_cat(a, b) lloyd_cat_internal(a, b)
