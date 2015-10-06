#pragma once

#define likely(x) __builtin_expect((x), 1)
