#pragma once

#include "lloyd_core_decoder.h"

#include "lloyd_decoder_internal.h"

#include lloyd_decoder_internal_h(core)

#define lloyd_core_decoder_state lloyd_decoder_get(core, state)

#define lloyd_core_decoder_init_args lloyd_decoder_get(core, init_args)

#define lloyd_core_decoder_init(args...) (lloyd_decoder(core, init, args))

#define lloyd_core_decoder_bitrate(args...) (lloyd_decoder(core, bitrate, args))

#define lloyd_core_decoder_read(args...) (lloyd_decoder(core, read, args))
