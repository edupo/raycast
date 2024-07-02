#pragma once

#include "ced/texture.h"
#include "ced/color.h"

typedef enum TileFlags{
    TILE_EMPTY    = 0b00000000,
    TILE_WALL     = 0b00000001,
    TILE_FLOOR    = 0b00000010,
    TILE_CEILING  = 0b00000100,
}TileFlags;

typedef struct {
    TileFlags flags;
    CedColor color;
    CedTexture* texture;
} Tile;

Tile* tile_palette_load(CedTextureManager* tm);
Tile* tile_palette_get(Tile* tile_palette, CedColor color);
void tile_palette_free(Tile* tile_palette);