#pragma once
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "vector.h"

#define TILE_SIZE 64.0

typedef struct {
    size_t width, height;
    size_t lenght;
    SDL_Color* data;
} Map;

Map* map_load(const char* file);
void map_free(Map* m);

SDL_Color map_get(const Map* map, const V2i* position);
