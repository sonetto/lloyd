#pragma once

#define clamp(value, min, max) ({ \
    typeof(value) _value = value; \
    typeof(min) _min = min; \
    typeof(max) _max = max; \
    \
    (_value > _max)? _max : \
    (_value < _min)? _min : \
    _value; \
})
