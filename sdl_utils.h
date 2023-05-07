#pragma once

#include <SDL2/SDL.h>
#include "vector.h"

SDL_Color surface_pixel_color(const SDL_Surface* surface, const V2i* position);
int color_eq(const SDL_Color a, const SDL_Color b);