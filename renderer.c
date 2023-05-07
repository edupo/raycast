#include "renderer.h"
#include "player.h"
#include "math.h"

const SDL_Color color_black =       (SDL_Color){0x1A,0x1C,0x2C,SDL_ALPHA_OPAQUE};
const SDL_Color color_white =       (SDL_Color){0xf4,0xf4,0xf4,SDL_ALPHA_OPAQUE};
const SDL_Color color_purple =      (SDL_Color){0x5D,0x27,0x5D,SDL_ALPHA_OPAQUE};
const SDL_Color color_red =         (SDL_Color){0xB1,0x3E,0x53,SDL_ALPHA_OPAQUE};
const SDL_Color color_orange =      (SDL_Color){0xEF,0x7D,0x57,SDL_ALPHA_OPAQUE};
const SDL_Color color_yellow =      (SDL_Color){0xFF,0xCD,0x75,SDL_ALPHA_OPAQUE};
const SDL_Color color_lime =        (SDL_Color){0xA7,0xF0,0x70,SDL_ALPHA_OPAQUE};
const SDL_Color color_green =       (SDL_Color){0x38,0xB7,0x64,SDL_ALPHA_OPAQUE};
const SDL_Color color_dark_cyan =   (SDL_Color){0x25,0x71,0x79,SDL_ALPHA_OPAQUE};
const SDL_Color color_dark_blue =   (SDL_Color){0x29,0x36,0x6F,SDL_ALPHA_OPAQUE};
const SDL_Color color_blue =        (SDL_Color){0x3B,0x5D,0xC9,SDL_ALPHA_OPAQUE};
const SDL_Color color_light_blue =  (SDL_Color){0x41,0xA6,0xF6,SDL_ALPHA_OPAQUE};
const SDL_Color color_light_cyan =  (SDL_Color){0x73,0xEF,0xF7,SDL_ALPHA_OPAQUE};
const SDL_Color color_light_grey =  (SDL_Color){0x94,0xB0,0xC2,SDL_ALPHA_OPAQUE};
const SDL_Color color_grey =        (SDL_Color){0x56,0x6C,0x86,SDL_ALPHA_OPAQUE};
const SDL_Color color_dark_grey =   (SDL_Color){0x33,0x3C,0x57,SDL_ALPHA_OPAQUE};
const SDL_Color color_transparent = (SDL_Color){0x00,0x00,0x00,SDL_ALPHA_TRANSPARENT};
const SDL_Color color_error =       (SDL_Color){0xFF,0x00,0xFF,SDL_ALPHA_OPAQUE};

inline void _set_color(SDL_Renderer* r, SDL_Color color)
{
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
}

Renderer* renderer_create(SDL_Renderer* renderer, SDL_Color background_color){
    Renderer* r = (Renderer*) malloc(sizeof(Renderer));
    r->renderer = renderer;
    r->bg_color = background_color;
    return r;
}

void renderer_free(Renderer* r){
    free(r);
}

void draw_clear(Renderer* r){
    _set_color(r->renderer, r->bg_color);
    SDL_RenderClear(r->renderer);
}

void draw_map(Renderer* r, Map* m, float scale)
{
    _set_color(r->renderer, color_white);
    int x, y;
    for (y = 0; y < m->height; y++)
    {
        for (x = 0; x < m->width; x++)
        {
            if (m->data[y * m->width + x] > 0) 
                SDL_RenderDrawRect(r->renderer, &(SDL_Rect){
                    x*scale, y*scale, scale - 1, scale - 1,
                });

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

void draw_frame(const Renderer* renderer, const Camera* camera, const Map* map, const V2i* size)
{

    for (int i = 0; i < size->x; i++)
    {
        float u = (2.0 * (float)i / (float)size->x - 1.0) * sinf(camera->fov / 2.0);
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
        float distance;
        V2i step;
        int hit = 0;
        int side;
        int cell_value;

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
            cell_value = map_get(map, map_coord.x, map_coord.y);
            if(cell_value < 0)
                break;
            else if (cell_value > 0)
                hit = 1;
        }

        if (hit == 0) continue;

        distance = (side == 0) ? 
            side_dist.x - delta_dist.x : 
            side_dist.y - delta_dist.y;

        int start, end;
        int line_height;
        SDL_Color color;

        line_height = size->y / distance;
        start = -line_height / 2 + size->y / 2;
        if(start < 0) start = 0;
        end = line_height / 2 + size->y / 2;
        if(end >= size->y) end = size->y;

        switch (cell_value)
        {
        case 1: color = (side) ? color_yellow : color_orange; break;
        case 2: color = (side) ? color_blue : color_dark_blue; break;
        case 3: color = (side) ? color_lime : color_green; break;
        case 4: color = (side) ? color_light_cyan : color_dark_cyan; break;
        case 5: color = (side) ? color_grey : color_dark_grey; break;
        default: color = color_error; break;
        }

        _set_color(renderer->renderer, color);
        SDL_RenderDrawLine(renderer->renderer, i, start, i, end);
    }
    
}

void renderer_present(Renderer* r){
    SDL_RenderPresent(r->renderer);
}