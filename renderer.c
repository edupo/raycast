#include "renderer.h"
#include "player.h"
#include "math.h"
#include "sdl_utils.h"
#include "config.h"
#include "texture.h"

const SDL_Color color_black =       {0x1A,0x1C,0x2C,SDL_ALPHA_OPAQUE};
const SDL_Color color_white =       {0xf4,0xf4,0xf4,SDL_ALPHA_OPAQUE};
const SDL_Color color_purple =      {0x5D,0x27,0x5D,SDL_ALPHA_OPAQUE};
const SDL_Color color_red =         {0xB1,0x3E,0x53,SDL_ALPHA_OPAQUE};
const SDL_Color color_orange =      {0xEF,0x7D,0x57,SDL_ALPHA_OPAQUE};
const SDL_Color color_yellow =      {0xFF,0xCD,0x75,SDL_ALPHA_OPAQUE};
const SDL_Color color_lime =        {0xA7,0xF0,0x70,SDL_ALPHA_OPAQUE};
const SDL_Color color_green =       {0x38,0xB7,0x64,SDL_ALPHA_OPAQUE};
const SDL_Color color_dark_cyan =   {0x25,0x71,0x79,SDL_ALPHA_OPAQUE};
const SDL_Color color_dark_blue =   {0x29,0x36,0x6F,SDL_ALPHA_OPAQUE};
const SDL_Color color_blue =        {0x3B,0x5D,0xC9,SDL_ALPHA_OPAQUE};
const SDL_Color color_light_blue =  {0x41,0xA6,0xF6,SDL_ALPHA_OPAQUE};
const SDL_Color color_light_cyan =  {0x73,0xEF,0xF7,SDL_ALPHA_OPAQUE};
const SDL_Color color_light_grey =  {0x94,0xB0,0xC2,SDL_ALPHA_OPAQUE};
const SDL_Color color_grey =        {0x56,0x6C,0x86,SDL_ALPHA_OPAQUE};
const SDL_Color color_dark_grey =   {0x33,0x3C,0x57,SDL_ALPHA_OPAQUE};
const SDL_Color color_transparent = {0x00,0x00,0x00,SDL_ALPHA_TRANSPARENT};
const SDL_Color color_error =       {0xFF,0x00,0xFF,SDL_ALPHA_OPAQUE};

inline void _set_color(SDL_Renderer* r, SDL_Color color)
{
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
}

Renderer* renderer_create(SDL_Renderer* renderer, SDL_Color background_color){
    Renderer* r = (Renderer*) malloc(sizeof(Renderer));
    r->renderer = renderer;
    r->bg_color = background_color;
    r->fog_color = background_color;
    r->fog_min_distance = FOG_MIN_DISTANCE;
    r->fog_max_distance = FOG_MAX_DISTANCE;
    return r;
}

void renderer_free(Renderer* r){
    free(r);
}

void draw_clear(Renderer* r){
    _set_color(r->renderer, r->bg_color);
    SDL_RenderClear(r->renderer);
    SDL_SetRenderDrawBlendMode(r->renderer, SDL_BLENDMODE_BLEND);
}

void draw_map(Renderer* r, Map* m, float scale)
{
    int x, y;
    for (y = 0; y < m->height; y++)
    {
        for (x = 0; x < m->width; x++)
        {
            SDL_Color color = map_get(m, &(V2i){x, y});
            if (color.a == SDL_ALPHA_TRANSPARENT) continue;

            color.a = 100;
            _set_color(r->renderer, color);
            SDL_RenderFillRect(r->renderer, 
                &(SDL_Rect){x*scale, y*scale, scale - 1, scale - 1}
            );

        }
    }
}

void draw_map_player(Renderer* r, Map* m, Player* p, float scale){
    float px = p->position.x * scale;
    float py = p->position.y * scale;
    _set_color(r->renderer, color_red);
    SDL_RenderFillRect(r->renderer, &(SDL_Rect){px-1, py-1, 3, 3}); 
    SDL_RenderDrawLine(r->renderer, 
        px, py, 
        px+p->direction.x*16, py+p->direction.y*16);
}

void draw_frame(const Renderer* renderer, const Camera* camera, const Map* map, V2i size, Textures* textures)
{

    for (int i = 0; i < size.x; i++)
    {
        float u = (2.0 * (float)i / (float)size.x - 1.0) * sinf(camera->fov / 2.0);
        V2f ray = {
            camera->dir.x + camera->plane.x * u, 
            camera->dir.y + camera->plane.y * u 
        };
        V2i map_coord = {(int) camera->pos.x, (int) camera->pos.y};
        V2f side_dist;
        V2f delta_dist = {
            (ray.x == 0) ? 1e30 : fabsf(1.0 / ray.x),
            (ray.y == 0) ? 1e30 : fabsf(1.0 / ray.y)
            // (ray.x == 0) ? 1e30 : sqrt(1 + (ray.y * ray.y) / (ray.x * ray.x)),
            // (ray.y == 0) ? 1e30 : sqrt(1 + (ray.x * ray.x) / (ray.y * ray.y))
        };
        V2i step;

        if(ray.x < 0){
            step.x = -1;
            side_dist.x = (camera->pos.x - map_coord.x) * delta_dist.x;
        }else{
            step.x = 1;
            side_dist.x = (map_coord.x + 1.0 - camera->pos.x) * delta_dist.x;
        }
        if(ray.y < 0){
            step.y = -1;
            side_dist.y = (camera->pos.y - map_coord.y) * delta_dist.y;
        }else{
            step.y = 1;
            side_dist.y = (map_coord.y + 1.0 - camera->pos.y) * delta_dist.y;
        }

        // DDA
        int hit = 0;
        int side;
        SDL_Color cell_value;

        while(hit == 0) {
            if(side_dist.x < side_dist.y){
                side_dist.x += delta_dist.x;
                map_coord.x += step.x;
                side = 0;
            }else{
                side_dist.y += delta_dist.y;
                map_coord.y += step.y;
                side = 1;
            }
            cell_value = map_get(map, &map_coord);
            if(color_eq(cell_value, color_error))
                break;
            else if (cell_value.a == SDL_ALPHA_OPAQUE)
                hit = 1;
        }
        if (hit == 0) continue;

        float distance;
        int line_height;

        if (side == 0)  {
            distance = side_dist.x - delta_dist.x;
            u = camera->pos.y + distance * ray.y;
        }else{

            distance = side_dist.y - delta_dist.y;
            u = camera->pos.x + distance * ray.x;
        }
        u -= floor(u);

        SDL_Texture* tex = textures_get(textures, 1);
        int tex_width, tex_height, tex_x;
        tex_x = (int)(u * tex_width);
        if((side == 0 && ray.x > 0) || (side == 1 && ray.y < 0))
            tex_x = 128 - tex_x - 1;
        SDL_QueryTexture(tex, NULL, NULL, &tex_width, &tex_height);

        int src_y, src_h;
        src_y = (tex_height >> 1) - (int)(0.5 * distance * tex_height);
        if(src_y < 0) src_y = 0;
        src_h = (int)(distance * tex_height);
        if(src_h > tex_height) src_h = tex_height;
        SDL_Rect src = {tex_x, src_y, 1, src_h};

        float line_scale = 1.0 / distance;
        int dst_y, dst_h;
        dst_y = (size.y >> 1) - (int)(0.5 * line_scale * size.y);
        if(dst_y < 0) dst_y = 0;
        dst_h = (int)(line_scale * size.y);
        if(dst_h > size.y) dst_h = size.y;
        SDL_Rect dst = {i, dst_y, 1, dst_h};

        SDL_RenderCopy(renderer->renderer, tex, &src, &dst);

        cell_value = color_lerp(
            color_transparent, 
            renderer->fog_color, 
            (distance - renderer->fog_min_distance) / (renderer->fog_max_distance - renderer->fog_min_distance));
        _set_color(renderer->renderer, cell_value);
        SDL_RenderDrawLine(renderer->renderer, i, dst.y, i, dst.y + dst.h);
    }
}

void renderer_present(Renderer* r){
    SDL_RenderPresent(r->renderer);
}