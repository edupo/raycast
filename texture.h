#pragma once

#include <SDL2/SDL.h>
#include "vector.h"

typedef struct {
    SDL_Texture** textures;
    size_t lenght;
} Textures;

Textures* textures_load(const SDL_Renderer* renderer, const char* files[], size_t n_files);
void textures_free(Textures* textures);
SDL_Texture* textures_get(const Textures* textures, size_t index);