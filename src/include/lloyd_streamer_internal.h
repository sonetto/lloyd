#pragma once

#include "cat.h"

#define lloyd_streamer_instance_decl(decoder) { \
    lloyd_decoder_get(decoder, instance) decoder_instance; \
    int bitrate; \
}
