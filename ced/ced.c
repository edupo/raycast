#include "ced.h"
#include "utils.h"

#define PIXELFORMAT SDL_PIXELFORMAT_RGBA32

const int UPDATE_INTERVAL = 1000/MAX_FPS;

Ced* ced_create(const V2i window_size, const char* window_title, const CedColor bg_color)
{
    Ced* ced = (Ced*) malloc(sizeof(Ced));

    SDL_Init(SDL_INIT_EVERYTHING);
    ced->window = SDL_CreateWindow(
        window_title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        window_size.x,
        window_size.y,
        SDL_WINDOW_SHOWN);
    ced->renderer = ced_renderer_create(ced->window, bg_color);
    SDL_SetWindowResizable(ced->window, SDL_TRUE);
    ced->screen_texture = SDL_CreateTexture(
        ced->renderer->renderer, 
        PIXELFORMAT,
        SDL_TEXTUREACCESS_TARGET,
        window_size.x, 
        window_size.y);

    ced-> frame_skip = 0;
    ced->window_title = window_title;

    ced->draw = NULL;
    ced->update = NULL;
    return ced;
}

void ced_free(Ced* s){
    SDL_free(s->screen_texture);
    SDL_free(s->renderer);
    SDL_free(s->window);
    free(s);
}

int ced_events(){
    CedEvent event;

    if (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT: return 0; break;
        default: break;
        }
    }
    return 1;
}

int ced_on_fps_change(Ced* ced, int fps){
    char title[128];
    sprintf(title, "%s - fps:%d", ced->window_title, fps);
    SDL_SetWindowTitle(ced->window, title);
}


void ced_run(Ced* ced){
    int running = 1;
    int past_ms = ced_get_ms();
    int present_ms = past_ms, past_fps = past_ms;
    int fps = 0, frames_skipped = 0;

    while ( running ){
        int elapsed_ms = 0;
        running = ced_events();
        present_ms= ced_get_ms();
        elapsed_ms = present_ms - past_ms;
        if (elapsed_ms >= UPDATE_INTERVAL){
            past_ms = present_ms;
            if(ced->update) ced->update(elapsed_ms);
            if( frames_skipped++ >= ced->frame_skip){
                if(ced->draw) ced->draw();
                ced_renderer_present(ced->renderer);
                fps++;
                frames_skipped = 0;
            }
        }

        if(present_ms - past_fps >= 1000){
            past_fps = present_ms;
            ced_on_fps_change(ced, fps);
            fps = 0;
        }
        ced_delay(clamp_u32(UPDATE_INTERVAL - elapsed_ms, 0, UPDATE_INTERVAL));
    }

}

inline uint32_t ced_get_ms(){
    return SDL_GetTicks();
}

inline void ced_delay(uint32_t ms){
    SDL_Delay(ms);
}
