#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "sdl_utils.h"
#include "renderer.h"

void map_free(Map* m){
    free(m->data);
}

Map* map_load(const char* file){
    SDL_Surface* surf = IMG_Load(file);
    Map* m = (Map*) malloc(sizeof(Map));

    m->width = surf->w;
    m->height = surf->h;
    m->lenght = m->width * m->height;
    m->data = (SDL_Color*) malloc(sizeof(SDL_Color) * m->lenght);

    for (size_t x = 0; x < m->width; x++)
    {
        for (size_t y = 0; y < m->height; y++)
        {
            V2i* pos = &(V2i){x, y};
            m->data[x + m->width * y] = surface_pixel_color(surf, pos);
        }
    }
    return m;
} 

SDL_Color map_get(const Map* m, const V2i* pos){
    int i = pos->x + m->width * pos->y;
    if(i >= m->lenght)
        return color_error;
    else
        return m->data[i];
}