#include "renderer_map.h"
// #include "../ced/types.h"
#include "../ced/color.h"

void draw_map(CedRenderer* r, Map* m, float scale)
{
    int x, y;
    for (y = 0; y < m->height; y++)
    {
        for (x = 0; x < m->width; x++)
        {
            Tile* tile = map_get(m, &(V2i){x, y});
            if (tile == NULL) continue;
            CedColor color = tile->color;
            if (color.a == SDL_ALPHA_TRANSPARENT) continue;

            color.a = 100;
            ced_renderer_set_color(r, color);
            SDL_RenderFillRect(r->renderer, 
                &(SDL_Rect){x*scale, y*scale, scale - 1, scale - 1}
            );

        }
    }
}

void draw_map_player(CedRenderer* r, Map* m, Player* p, float scale){
    float px = p->position.x * scale;
    float py = p->position.y * scale;
    ced_renderer_set_color(r, color_red);
    SDL_RenderFillRect(r->renderer, &(SDL_Rect){px-1, py-1, 3, 3}); 
    SDL_RenderDrawLine(r->renderer, 
        px, py, 
        px+p->direction.x*16, py+p->direction.y*16);
}