#pragma once
#include <stdlib.h>

#include "vector.h"

#define TILE_SIZE 64.0

typedef struct {
    size_t width, height;
    size_t lenght;
    float tile_size;
    int* data;
} Map;

Map* map_create(size_t width, size_t height, int* data);
void map_free(Map* m);

V2i map_point_to_coord(Map* m, V2f pos);
