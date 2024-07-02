#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct { int x, y; }       V2i;
typedef struct { float x, y; }     V2f;
typedef struct { double x, y; }    V2d;

typedef struct { int x, y, z; }    V3i;
typedef struct { float x, y, z; }  V3f;
typedef struct { double x, y, z; } V3d;

typedef uint32_t                   Hash;
typedef uint32_t                   Flags;

typedef SDL_Window                 CedWindow;
typedef SDL_Texture                CedTexture;
typedef SDL_Color                  CedColor;
typedef SDL_Event                  CedEvent;
