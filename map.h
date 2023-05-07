#pragma once
#include <stdlib.h>

#include "vector.h"

#define TILE_SIZE 64.0

typedef struct {
    size_t width, height;
    size_t lenght;
    int* data;
} Map;

Map* map_create(size_t width, size_t height, int* data);
void map_free(Map* m);
int map_get(const Map* m, int x, int y);
