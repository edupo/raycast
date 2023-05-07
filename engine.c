#include "engine.h"

#define PIXELFORMAT SDL_PIXELFORMAT_RGBA32

const int MAX_FPS = 60;
const int UPDATE_INTERVAL = 1000/MAX_FPS;

Engine* engine_create(int width, int height, char* title){
    Engine* s = (Engine*) malloc(sizeof(Engine));

    SDL_Init(SDL_INIT_EVERYTHING);
    s->window = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width,
        height,
        SDL_WINDOW_SHOWN);
    s->renderer = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetWindowResizable(s->window, SDL_TRUE);
    s->screen_texture = SDL_CreateTexture(
        s->renderer, 
        PIXELFORMAT,
        SDL_TEXTUREACCESS_TARGET,
        width, 
        height);
    s->screen_surface = SDL_CreateRGBSurfaceWithFormat(
        0, 
        width, 
        height, 
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
    int past = SDL_GetTicks();
    int now = past, past_fps = past;
    int fps = 0, frames_skipped = 0;

    while ( running ){
        int time_elapsed = 0;
        running = engine_events();
        now=SDL_GetTicks();
        time_elapsed = now - past;
        if (time_elapsed >= UPDATE_INTERVAL){
            past = now;
            if(engine->update) engine->update(time_elapsed);
            if( frames_skipped++ >= engine->frame_skip){
                if(engine->draw) engine->draw();
                fps++;
                frames_skipped = 0;
            }
        }

        if(now - past_fps >= 1000){
            past_fps = now;
            engine_on_fps_change(engine, fps);
            fps = 0;
        }
        SDL_Delay(UPDATE_INTERVAL/4);
    }

}