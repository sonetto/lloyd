#pragma once

#include <vorbis/vorbisfile.h>
#include "cat.h"
#include "lloyd_ogg_vorbis_decoder.h"

#define lloyd_ogg_vorbis_decoder_instance OggVorbis_File

#define lloyd_ogg_vorbis_decoder_init_return_type void
#define lloyd_ogg_vorbis_decoder_init_params const char *file_path
#define lloyd_ogg_vorbis_decoder_init_args file_path

#define prefix(s) cat(lloyd_ogg_vorbis_decoder_, s)

prefix(init_return_type)
lloyd_ogg_vorbis_decoder_init(
    prefix(instance) *instance,
    prefix(init_params)
);

int lloyd_ogg_vorbis_decoder_bitrate(prefix(instance) *instance);

int lloyd_ogg_vorbis_decoder_read(
    prefix(instance) *instance,
    void *buf, int len
);
