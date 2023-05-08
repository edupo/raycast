#include <stdlib.h>
#include <SDL2/SDL_image.h>

#include "texture.h"

Textures* textures_load(const SDL_Renderer* r, const char* files[], size_t n_files){
    Textures* t = malloc(sizeof(Textures));
    t->lenght = n_files;
    t->textures = malloc(t->lenght * sizeof(SDL_Texture*));

    for (size_t i = 0; i < t->lenght; i++)
    {
        char path[256];
        sprintf(path, "textures/%s", files[i]);
        t->textures[i] = IMG_LoadTexture(r, path);      
    }
    return t;
}

void textures_free(Textures* t){
    for (size_t i = 0; i < t->lenght; i++)
    {
        SDL_DestroyTexture(t->textures[i]);
    }
    free(t->textures);
    free(t);
}

inline SDL_Texture* textures_get(const Textures* textures, size_t index){
    return textures->textures[index];
}