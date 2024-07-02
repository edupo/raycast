#pragma once

#include "types.h"

#ifndef FOG_MIN_DISTANCE
#define FOG_MIN_DISTANCE 3.0
#endif
#ifndef FOG_MAX_DISTANCE
#define FOG_MAX_DISTANCE 15.0
#endif

typedef struct{
    CedColor bg_color;
    SDL_Renderer* renderer;
    float fog_min_distance, fog_max_distance;
    CedColor fog_color;
} CedRenderer;


CedRenderer* ced_renderer_create(CedWindow* window, const CedColor background_color);
void ced_renderer_free(CedRenderer* r);

void ced_renderer_set_color(const CedRenderer* r, const CedColor color);
void ced_renderer_clear(const CedRenderer* renderer);
void ced_renderer_present(const CedRenderer* renderer);