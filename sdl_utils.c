#include "sdl_utils.h"

// From: https://discourse.libsdl.org/t/how-do-i-get-the-rgb-values-of-a-pixel-from-a-given-surface-and-x-and-y-coordinates-in-sdl2/26915/2
SDL_Color surface_pixel_color(const SDL_Surface* surface, const V2i* pos)
{
	const Uint8 bpp = surface->format->BytesPerPixel;
	Uint8* pixel = (Uint8*)surface->pixels + pos->y * surface->pitch + pos->x * bpp;
	Uint32 pixel_data = *(Uint32*)pixel;
	SDL_Color color = {0x00, 0x00, 0x00, 0x00};

	SDL_GetRGBA(pixel_data, surface->format, &color.r, &color.g, &color.b, &color.a);

	return color;
}

int color_eq(const SDL_Color a, const SDL_Color b){
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}