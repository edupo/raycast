#include "engine.h"

#define PIXELFORMAT SDL_PIXELFORMAT_RGBA32

const int UPDATE_INTERVAL = 1000/MAX_FPS;

Engine* engine_create(V2i window_size, char* title){
    Engine* s = (Engine*) malloc(sizeof(Engine));

    SDL_Init(SDL_INIT_EVERYTHING);
    s->window = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        window_size.x,
        window_size.y,
        SDL_WINDOW_SHOWN);
    s->renderer = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetWindowResizable(s->window, SDL_TRUE);
    s->screen_texture = SDL_CreateTexture(
        s->renderer, 
        PIXELFORMAT,
        SDL_TEXTUREACCESS_TARGET,
        window_size.x, 
        window_size.y);
    s->screen_surface = SDL_CreateRGBSurfaceWithFormat(
        0, 
        window_size.x, 
        window_size.y, 
        32, 
        PIXELFORMAT);

    s-> frame_skip = 0;
    s->window_title = title;

    s->draw = NULL;
    s->update = NULL;
    return s;
}

void engine_free(Engine* s){
    SDL_free(s->screen_surface);
    SDL_free(s->screen_texture);
    SDL_free(s->renderer);
    SDL_free(s->window);
    free(s);
}

int engine_events(){
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT: return 0; break;
        default: break;
        }
    }
    return 1;
}

int engine_on_fps_change(Engine* engine, int fps){
    char title[128];
    sprintf(title, "%s - fps:%d", engine->window_title, fps);
    SDL_SetWindowTitle(engine->window, title);
}

void engine_run(Engine* engine){
    int running = 1;
    int past_ms = SDL_GetTicks();
    int present_ms = past_ms, past_fps = past_ms;
    int fps = 0, frames_skipped = 0;

    while ( running ){
        int elapsed_ms = 0;
        running = engine_events();
        present_ms=SDL_GetTicks();
        elapsed_ms = present_ms - past_ms;
        if (elapsed_ms >= UPDATE_INTERVAL){
            past_ms = present_ms;
            if(engine->update) engine->update(elapsed_ms);
            if( frames_skipped++ >= engine->frame_skip){
                if(engine->draw) engine->draw();
                fps++;
                frames_skipped = 0;
            }
        }

        if(present_ms - past_fps >= 1000){
            past_fps = present_ms;
            engine_on_fps_change(engine, fps);
            fps = 0;
        }
        SDL_Delay(SDL_clamp(UPDATE_INTERVAL - elapsed_ms, 0, UPDATE_INTERVAL));
    }

}