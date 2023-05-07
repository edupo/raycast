#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "map.h"
#include "vector.h"
#include "engine.h"
#include "renderer.h"
#include "camera.h"
#include "math.h"

#define WIDTH 640 
#define HEIGHT 480 
#define RAYS WIDTH 
#define MIN_MAP_SCALE 4

#ifdef main
# undef main
#endif

V2i* screen_size = &(V2i){WIDTH, HEIGHT};
Engine* engine;
Renderer* renderer;
Player* player;
Map* map;
Camera* camera;

float fov;
float ray_angle; 

void update()
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    if(keyboard[SDL_SCANCODE_UP] || keyboard[SDL_SCANCODE_W])
        player_move_forward(player);
    else if(keyboard[SDL_SCANCODE_DOWN] || keyboard[SDL_SCANCODE_S])
        player_move_backwards(player);

    if(keyboard[SDL_SCANCODE_LEFT] || keyboard[SDL_SCANCODE_A])
        player_set_angle(player, player->angle-=.1);
    else if(keyboard[SDL_SCANCODE_RIGHT] || keyboard[SDL_SCANCODE_D])
        player_set_angle(player, player->angle+=.1);
    
    camera_place(camera, player->position, player->direction);
}

void draw()
{
    draw_clear(renderer);
    draw_frame(renderer, camera, map, screen_size);
    draw_map(renderer, map, MIN_MAP_SCALE);
    draw_map_player(renderer, map, player, MIN_MAP_SCALE);
    renderer_present(renderer);
}

int main(int argc, char **argv)
{
    player = player_create(4.0, 4.0, 0.0, 0.03);
    map = map_load("level1.png");
    engine = engine_create(WIDTH, HEIGHT, "gameto");
    renderer = renderer_create(engine->renderer, color_black);
    camera = camera_create(deg2rad(90.0));
    fov = C_PI2;
    ray_angle = fov / RAYS;

    engine->draw = draw;
    engine->update = update;

    engine_run(engine);

    renderer_free(renderer);
    engine_free(engine);
    player_free(player);
    map_free(map);
    camera_free(camera);

    return 0;
}