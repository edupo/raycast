#pragma once
#include <SDL2/SDL.h>

#include "map.h"
#include "player.h"
#include "camera.h"
#include "texture.h"

extern const SDL_Color color_black;
extern const SDL_Color color_white;
extern const SDL_Color color_purple;
extern const SDL_Color color_red;
extern const SDL_Color color_orange;
extern const SDL_Color color_yellow;
extern const SDL_Color color_lime;
extern const SDL_Color color_green;
extern const SDL_Color color_dark_cyan;
extern const SDL_Color color_dark_blue;
extern const SDL_Color color_blue;
extern const SDL_Color color_light_blue;
extern const SDL_Color color_light_cyan;
extern const SDL_Color color_light_grey;
extern const SDL_Color color_grey;
extern const SDL_Color color_dark_grey;
extern const SDL_Color color_transparent;
extern const SDL_Color color_error;

typedef struct{
    SDL_Color bg_color;
    SDL_Renderer* renderer;
    float fog_min_distance, fog_max_distance;
    SDL_Color fog_color;
} Renderer;

void _set_color(SDL_Renderer* r, SDL_Color color);

Renderer* renderer_create(SDL_Renderer* renderer, SDL_Color background_color);
void renderer_free(Renderer* r);

void draw_clear(Renderer* renderer);
void draw_map(Renderer* renderer, Map* map, float scale);
void draw_map_player(Renderer* renderer, Map* map, Player* p, float scale);
void draw_frame(const Renderer* renderer, const Camera* camera, const Map* map, V2i size, Textures* textures);

void renderer_present(Renderer* r);