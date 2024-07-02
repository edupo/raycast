#pragma once

#include <stdlib.h>

#include "ced/types.h"
#include "ced/texture.h"

#include "tiles.h"

typedef struct {
    size_t width, height;
    size_t lenght;
    Tile** data;
} Map;

Map* map_load(const char* file, Tile* tile_palette);
void map_free(Map* m);

Tile* map_get(const Map* map, const V2i* position);
Tile* map_get_coords(const Map* m, int x, int y);
