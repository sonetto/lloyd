#pragma once

#define cat_internal(a, b) a##b
#define cat(a, b) cat_internal(a, b)
