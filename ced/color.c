#include "color.h"
#include "utils.h"

const CedColor color_black =       {0x18,0x14,0x25,SDL_ALPHA_OPAQUE};
const CedColor color_white =       {0xf4,0xf4,0xf4,SDL_ALPHA_OPAQUE};
const CedColor color_purple =      {0x5D,0x27,0x5D,SDL_ALPHA_OPAQUE};
const CedColor color_red =         {0xB1,0x3E,0x53,SDL_ALPHA_OPAQUE};
const CedColor color_orange =      {0xF7,0x76,0x22,SDL_ALPHA_OPAQUE};
const CedColor color_brown =       {0xBE,0x4A,0x2F,SDL_ALPHA_OPAQUE};
const CedColor color_yellow =      {0xFF,0xCD,0x75,SDL_ALPHA_OPAQUE};
const CedColor color_lime =        {0xA7,0xF0,0x70,SDL_ALPHA_OPAQUE};
const CedColor color_green =       {0x63,0xC7,0x4D,SDL_ALPHA_OPAQUE};
const CedColor color_dark_cyan =   {0x25,0x71,0x79,SDL_ALPHA_OPAQUE};
const CedColor color_dark_blue =   {0x29,0x36,0x6F,SDL_ALPHA_OPAQUE};
const CedColor color_blue =        {0x3B,0x5D,0xC9,SDL_ALPHA_OPAQUE};
const CedColor color_light_blue =  {0x41,0xA6,0xF6,SDL_ALPHA_OPAQUE};
const CedColor color_light_cyan =  {0x73,0xEF,0xF7,SDL_ALPHA_OPAQUE};
const CedColor color_light_grey =  {0x94,0xB0,0xC2,SDL_ALPHA_OPAQUE};
const CedColor color_grey =        {0x56,0x6C,0x86,SDL_ALPHA_OPAQUE};
const CedColor color_dark_grey =   {0x33,0x3C,0x57,SDL_ALPHA_OPAQUE};
const CedColor color_transparent = {0x00,0x00,0x00,SDL_ALPHA_TRANSPARENT};
const CedColor color_error =       {0xFF,0x00,0xFF,SDL_ALPHA_OPAQUE};

inline int ced_color_eq(const CedColor a, const CedColor b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

CedColor ced_color_lerp(const CedColor a, const CedColor b, float value)
{
	CedColor c = a;
	value = clamp_f32(value, 0.0, 1.0);	
	c.r += (((int16_t) b.r - (int16_t) a.r ) * value);
	c.g += (((int16_t) b.g - (int16_t) a.g ) * value);
	c.b += (((int16_t) b.b - (int16_t) a.b ) * value);
	c.a += (((int16_t) b.a - (int16_t) a.a ) * value);
	return c;
}