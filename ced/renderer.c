#include <SDL2/SDL.h>

#include "renderer.h"
#include "utils.h"

inline void ced_renderer_set_color(const CedRenderer* r, const CedColor color)
{
    SDL_SetRenderDrawColor(r->renderer, color.r, color.g, color.b, color.a);
}

CedRenderer* ced_renderer_create(CedWindow* window, const CedColor background_color){
    CedRenderer* r = (CedRenderer*) malloc(sizeof(CedRenderer));
    r->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    r->bg_color = background_color;
    r->fog_color = background_color;
    r->fog_min_distance = FOG_MIN_DISTANCE;
    r->fog_max_distance = FOG_MAX_DISTANCE;
    return r;
}

void ced_renderer_free(CedRenderer* r){
    SDL_DestroyRenderer(r->renderer);
    free(r);
}

void ced_renderer_clear(const CedRenderer* r){
    ced_renderer_set_color(r, r->bg_color);
    SDL_RenderClear(r->renderer);
    SDL_SetRenderDrawBlendMode(r->renderer, SDL_BLENDMODE_BLEND);
}


void ced_renderer_present(const CedRenderer* r){
    SDL_RenderPresent(r->renderer);
}