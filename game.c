#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "player.h"
#include "map.h"
#include "vector.h"
#include "engine.h"
#include "renderer.h"
#include "camera.h"
#include "math.h"

#ifdef main
# undef main
#endif

V2i window_size = (V2i){WINDOW_WIDTH, WINDOW_HEIGHT};
Engine* engine;
Renderer* renderer;
Player* player;
Map* map;
Camera* camera;

void update(Uint32 delta_ms)
{
    float delta_s = delta_ms / 1000.0;
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    if(keyboard[SDL_SCANCODE_UP] || keyboard[SDL_SCANCODE_W])
        player->command.forward = 1.0;
    else if(keyboard[SDL_SCANCODE_DOWN] || keyboard[SDL_SCANCODE_S])
        player->command.forward = -1.0;
    else
        player->command.forward = 0.0;

    if(keyboard[SDL_SCANCODE_Q])
        player->command.strafe = -1.0;
    else if(keyboard[SDL_SCANCODE_E])
        player->command.strafe = 1.0;
    else
        player->command.strafe = 0.0;

    if(keyboard[SDL_SCANCODE_LEFT] || keyboard[SDL_SCANCODE_A])
        player->command.rotation = -1.0;
    else if(keyboard[SDL_SCANCODE_RIGHT] || keyboard[SDL_SCANCODE_D])
        player->command.rotation = 1.0;
    else
        player->command.rotation = 0.0;
    
    player_update(player, delta_s);
    camera_place(camera, player->position, player->direction);
}

void draw()
{
    draw_clear(renderer);
    draw_frame(renderer, camera, map, window_size);
    draw_map(renderer, map, MINIMAP_SCALE);
    draw_map_player(renderer, map, player, MINIMAP_SCALE);
    renderer_present(renderer);
}

int main(int argc, char **argv)
{
    player = player_create((V2f){4.0, 4.0}, 0.0);
    map = map_load("level1.png");
    engine = engine_create(window_size, "gameto");
    renderer = renderer_create(engine->renderer, color_black);
    camera = camera_create(deg2rad(90.0));

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