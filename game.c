#include <stdio.h>
#include <stdlib.h>

#include "ced/ced.h"
#include "ced/camera.h"
#include "ced/color.h"
#include "ced/texture.h"
#include "ced/utils.h"

#include "renderer_map.h"
#include "renderer_wall.h"
#include "config.h"
#include "player.h"
#include "map.h"
#include "tiles.h"

#ifdef main
# undef main 
#endif

V2i window_size = (V2i){WINDOW_WIDTH, WINDOW_HEIGHT};
Ced* ced;
CedRenderer* renderer;
Player* player;
Map* map;
CedCamera* camera;
CedTextureManager* texture_manager;
Tile* tile_palette;

WallRenderer* wall_renderer;

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
    ced_camera_place(camera, player->position, player->direction);
}

void draw()
{
    wall_renderer_cast(wall_renderer, camera, map);

    ced_renderer_clear(ced->renderer);
    draw_map(ced->renderer, map, MINIMAP_SCALE);
    draw_map_player(ced->renderer, map, player, MINIMAP_SCALE);
    wall_renderer_draw_textures(wall_renderer, ced->renderer);
}

void game_init(){
    player = player_create((V2f){4.0, 4.0}, 0.0);
    ced = ced_create(window_size, "gameto", color_black);
    texture_manager = ced_texture_manager_create(ced->renderer, 10);
    tile_palette = tile_palette_load(texture_manager);
    map = map_load("level1.png", tile_palette);
    camera = ced_camera_create(deg2rad(90.0));
    wall_renderer = wall_renderer_create(window_size);

    ced->draw = draw;
    ced->update = update;
}

void game_free(){
    player_free(player);
    map_free(map);
    wall_renderer_free(wall_renderer);
    tile_palette_free(tile_palette);

    ced_camera_free(camera);
    ced_texture_manager_free(texture_manager);
    ced_free(ced);
}

int main(int argc, char **argv)
{
    game_init();
    ced_run(ced);
    game_free();
    return 0;
}