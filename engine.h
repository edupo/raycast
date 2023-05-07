#pragma once
#include <SDL2/SDL.h>

#include "vector.h"

#ifndef MAX_FPS 
    #define MAX_FPS 60
#endif

extern const int UPDATE_INTERVAL;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screen_texture;
    SDL_Surface* screen_surface;

    int frame_skip;
    char* window_title;

    void (*update)(Uint32);
    void (*draw)();
} Engine;

Engine* engine_create(V2i window_size, char* window_title);
void engine_free(Engine* engine);

void engine_run(Engine* engine);