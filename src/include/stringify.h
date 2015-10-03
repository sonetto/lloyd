#pragma once

#define stringify_internal(value) #value
#define stringify(value) stringify_internal(value)
