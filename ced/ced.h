#pragma once

#ifndef MAX_FPS 
    #define MAX_FPS 60
#endif

#include "types.h"
#include "renderer.h"

extern const int UPDATE_INTERVAL;
typedef struct {
    CedWindow* window;
    CedRenderer* renderer;
    CedTexture* screen_texture;

    int frame_skip;
    const char* window_title;

    void (*update)(Uint32);
    void (*draw)();
} Ced;


Ced* ced_create(const V2i window_size, const char* window_title, const CedColor bg_color);
void ced_free(Ced* ced);

void ced_run(Ced* ced);
uint32_t ced_get_ms();
void ced_delay(uint32_t ms);
