#pragma once

struct lloyd_source_data {
    int allocated;
    unsigned al_source;
};

struct lloyd_source_data *lloyd_source_alloc();
void lloyd_source_free(struct lloyd_source_data *source);
