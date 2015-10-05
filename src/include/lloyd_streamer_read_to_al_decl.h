#pragma once

#include "lloyd_streamer_prefix.h"

#define lloyd_streamer_read_to_al_decl(streamer) \
    int lloyd_streamer_prefix(streamer, read_to_al)( \
        lloyd_streamer_prefix(streamer, state) *streamer_state, \
        unsigned al_buf \
    )
