#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "ced/color.h"
#include "ced/texture.h"

Tile tile_empty;
Tile tile_brick;

void map_free(Map* m){
    free(m->data);
}

// From: https://discourse.libsdl.org/t/how-do-i-get-the-rgb-values-of-a-pixel-from-a-given-surface-and-x-and-y-coordinates-in-sdl2/26915/2
SDL_Color _surface_pixel_color(const SDL_Surface* surface, const V2i* pos)
{
	const Uint8 bpp = surface->format->BytesPerPixel;
	Uint8* pixel = (Uint8*)surface->pixels + pos->y * surface->pitch + pos->x * bpp;
	Uint32 pixel_data = *(Uint32*)pixel;
	SDL_Color color = {0x00, 0x00, 0x00, 0x00};

	SDL_GetRGBA(pixel_data, surface->format, &color.r, &color.g, &color.b, &color.a);

	return color;
}

Map* map_load(const char* file, Tile* tile_palette){

    SDL_Surface* surf = IMG_Load(file);
    Map* m = (Map*) malloc(sizeof(Map));

    m->width = surf->w;
    m->height = surf->h;
    m->lenght = m->width * m->height;
    m->data = (Tile**) malloc(sizeof(Tile*) * m->lenght);

    for (size_t x = 0; x < m->width; x++)
    {
        for (size_t y = 0; y < m->height; y++)
        {
            V2i* pos = &(V2i){x, y};
            // TODO: mapping between color and tile.
            m->data[x + m->width * y] = tile_palette_get(
                tile_palette, _surface_pixel_color(surf, pos));
        }
    }
    return m;
} 

inline Tile* map_get(const Map* m, const V2i* pos){
    return map_get_coords(m, pos->x, pos->y);
}

Tile* map_get_coords(const Map* m, int x, int y){
    int i = x + m->width * y;
    if(i >= m->lenght)
        return NULL;
    else
        return m->data[i];
}