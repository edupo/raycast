#pragma once
#include <SDL2/SDL.h>

extern const int MAX_FPS;
extern const int UPDATE_INTERVAL;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screen_texture;
    SDL_Surface* screen_surface;

    int frame_skip;
    char* window_title;

    void (*update)(int);
    void (*draw)();
} Engine;

Engine* engine_create(int window_width, int window_height, char* window_title);
void engine_free(Engine* engine);

void engine_run(Engine* engine);