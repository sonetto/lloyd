#pragma once

#include "lloyd_core_decoder.h"

#include "lloyd_decoder_internal.h"

#include lloyd_decoder_internal_h(core)

#define lloyd_core_decoder_instance lloyd_decoder_get(core, instance)

#define lloyd_core_decoder_init_args lloyd_decoder_get(core, init_args)
