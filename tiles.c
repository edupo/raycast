#include "tiles.h"

#define _TILE_PALETTE_SIZE 4
Tile* tile_palette_load(CedTextureManager* tm){

    Tile* tile_palete = (Tile[]){ 
        (Tile){
            TILE_EMPTY | TILE_FLOOR | TILE_CEILING, 
            color_black, 
            NULL}, 
        (Tile){
            TILE_WALL, 
            color_orange, 
            ced_texture_manager_get_by_path(tm, "default_brick.png")},
        (Tile){
            TILE_WALL, 
            color_brown, 
            ced_texture_manager_get_by_path(tm, "default_brick.png")},
        (Tile){
            TILE_EMPTY | TILE_FLOOR, 
            color_green, 
            ced_texture_manager_get_by_path(tm, "default_grass.png")},
    };

    return tile_palete;

}

Tile* tile_palette_get(Tile* tile_palette, CedColor color){
    for (size_t i = 0; i < _TILE_PALETTE_SIZE; i++)
    {
        if (ced_color_eq(color, tile_palette[i].color))
            return &tile_palette[i];
    }
    return NULL;
}

void tile_palette_free(Tile* tile_palette){
    for (size_t i = 0; i < _TILE_PALETTE_SIZE; i++)
    {
        free(&tile_palette[i]);
    }
}