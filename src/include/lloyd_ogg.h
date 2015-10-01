#pragma once

#include <vorbis/vorbisfile.h>

#define lloyd_ogg_eof (-1)

void lloyd_ogg_open(const char *file_path, OggVorbis_File *ogg_file);

int lloyd_ogg_read(OggVorbis_File *ogg_file, unsigned al_buf);
