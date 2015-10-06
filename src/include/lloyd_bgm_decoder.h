#pragma once

#include "lloyd_cat_string.h"
#include "lloyd_default_decoder_name.h"

#define lloyd_bgm_decoder_backend_name lloyd_default_decoder_name

#include lloyd_cat_string(lloyd_bgm_decoder_backend_name, decoder.h)

#define lloyd_bgm_decoder \
    lloyd_cat(lloyd_bgm_decoder_backend_name, decoder)

#define lloyd_bgm_decoder_h lloyd_bgm_decoder(h)
