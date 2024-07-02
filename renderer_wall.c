#include "renderer_wall.h"
#include "SDL2/SDL.h"

WallRenderer* wall_renderer_create(V2i size){
    WallRenderer* wr = malloc(sizeof(WallRenderer));
    wr->raycasts = malloc(sizeof(WallRaycast) * size.x);
    wr->size = size;
    return wr;
}

void wall_renderer_free(WallRenderer* wr){
    free(wr->raycasts);
    free(wr);
}

void wall_renderer_cast(WallRenderer* wr, const CedCamera* camera, const Map* map)
{
    float u, distance;
    int hit, side, projection_y, projection_height;
    Tile* tile;
    float dir_x, dir_y;
    float d_dist_x, d_dist_y; // Delta distance
    float side_dist_x, side_dist_y; // Side distance
    int coord_x, coord_y, step_x, step_y;

    int w = wr->size.x;
    int h = wr->size.y;
    float pos_x = camera->pos.x, pos_y = camera->pos.y;
    WallRaycast* rc;

    for (int i = 0; i < w; i++)
    {
        u = (2.0 * (float)i / (float)w - 1.0) * sinf(camera->fov / 2.0);
        dir_x = camera->dir.x + camera->plane.x * u;
        dir_y = camera->dir.y + camera->plane.y * u;
        d_dist_x = (dir_x == 0) ? 1e30 : fabsf(1.0 / dir_x);
        d_dist_y = (dir_y == 0) ? 1e30 : fabsf(1.0 / dir_y);
        //d_dist_x = (ray.x == 0) ? 1e30 : sqrt(1 + (ray.y * ray.y) / (ray.x * ray.x));
        //d_dist_y = (ray.y == 0) ? 1e30 : sqrt(1 + (ray.x * ray.x) / (ray.y * ray.y))
        coord_x = (int) pos_x;
        coord_y = (int) pos_y;

        if(dir_x < 0){
            step_x = -1;
            side_dist_x = (pos_x - coord_x) * d_dist_x;
        }else{
            step_x = 1;
            side_dist_x = (coord_x + 1.0 - pos_x) * d_dist_x;
        }
        if(dir_y < 0){
            step_y = -1;
            side_dist_y = (pos_y - coord_y) * d_dist_y;
        }else{
            step_y = 1;
            side_dist_y = (coord_y + 1.0 - pos_y) * d_dist_y;
        }

        // DDA
        hit = 0;
        do{
            if(side_dist_x < side_dist_y){
                side_dist_x += d_dist_x;
                coord_x += step_x;
                side = 0;
            }else{
                side_dist_y += d_dist_y;
                coord_y += step_y;
                side = 1;
            }

            tile = map_get_coords(map, coord_x, coord_y);
            if(tile == NULL)
                break;
            else if (tile->flags & TILE_WALL)
                hit = 1;

        }while(hit == 0);

        rc = &wr->raycasts[i];
        rc->flags = hit * WALL_RENDERER_HIT | side * WALL_RENDERER_SIDE;
        if (hit == 0) continue;

        if (side == 0)  {
            distance = side_dist_x - d_dist_x;
            u = pos_y + distance * dir_y;
        }else{

            distance = side_dist_y - d_dist_y;
            u = pos_x + distance * dir_x;
        }

        projection_height = 1.0 / distance * h;
        projection_y = (h - projection_height) >> 1;

        rc->projection_y = (projection_y < 0)? 0: projection_y;
        rc->projection_height = (projection_height> h)? h : projection_height;
        rc->direction = (V2f){dir_x, dir_y};
        rc->distance = distance;
        rc->tile_coord = (V2i){coord_x, coord_y};
        rc->tile = tile;
        rc->u = u - floor(u);
    }
}

void wall_renderer_draw_textures(const WallRenderer* wr, const CedRenderer* renderer){
    int w = wr->size.x;
    int h = wr->size.y;
    int side;
    WallRaycast* rc;
    WallRaycastFlags flags;
    float distance;
    SDL_Texture* tex;
    int tex_width, tex_h, tex_x;
    int dst_y, dst_h, src_y, src_h;
    float projection;
    SDL_Rect src, dst;
    src.w = 1; // We copy vertical lines (1 px)
    dst.w = 1;

    for (int i = 0; i < w; i++){
        rc = &wr->raycasts[i];
        flags = rc->flags;
        if (!flags & WALL_RENDERER_HIT || rc->tile == NULL) continue;

        side = flags | WALL_RENDERER_SIDE;
        distance = rc->distance;
        tex = rc->tile->texture;
        SDL_QueryTexture(tex, NULL, NULL, &tex_width, &tex_h);

        tex_x = (int)(rc->u * tex_width);
        if((side == 0 && rc->direction.x > 0) || (side != 0 && rc->direction.y < 0))
            tex_x = 128 - tex_x - 1;

        src_h = distance * tex_h;
        src_y = (tex_h - src_h) >> 1;
        src.x = tex_x;
        src.y = (src_y < 0) ? 0 : src_y;
        src.h = (src_h > tex_h) ? tex_h : src_h;

        dst.x = i;
        dst.y = rc->projection_y;
        dst.h = rc->projection_height;

        SDL_RenderCopy(renderer->renderer, tex, &src, &dst);
    }
}