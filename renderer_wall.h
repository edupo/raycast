#pragma once

#include "../ced/renderer.h"
#include "../ced/camera.h"
#include "../map.h"

typedef enum WallRaycastFlags {
   WALL_RENDERER_NONE = 0b00000000,
   WALL_RENDERER_HIT  = 0b00000001,
   WALL_RENDERER_SIDE = 0b00000010,
   WALL_RENDERER_FOG  = 0b00000100,
}WallRaycastFlags;

typedef struct{
    WallRaycastFlags flags; 
    V2f direction;
    float distance;
    Tile* tile;
    V2i tile_coord;
    float u;
    int projection_y;
    int projection_height;
} WallRaycast;

typedef struct{
    V2i size;
    WallRaycast* raycasts;
} WallRenderer;

WallRenderer* wall_renderer_create(V2i size);
void wall_renderer_free(WallRenderer* wall_renderer);
void wall_renderer_cast(WallRenderer* wall_renderer, const CedCamera* camera, const Map* map);
void wall_renderer_draw_textures(const WallRenderer* wall_renderer, const CedRenderer* renderer);
void wall_renderer_draw_depth(const WallRenderer* wall_renderer, const CedRenderer* renderer);
void wall_renderer_draw_fog(const WallRenderer* wall_renderer, const CedRenderer* renderer);
void wall_renderer_draw_mask(const WallRenderer* wall_renderer, const CedRenderer* renderer);