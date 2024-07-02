#include <stdio.h>
#include <SDL2/SDL_image.h>

#include "texture.h"
#include "utils.h"

inline void ced_texture_free(CedTexture* texture){
    SDL_DestroyTexture(texture);
}

CedTextureManager* ced_texture_manager_create(CedRenderer* renderer, size_t capacity){
    if (!renderer)
    {
        printf("[CRITICAL]: No renderer passed on CedTextureManager creation!");
        exit(-1);
    }
    
    CedTextureManager* ct = malloc(sizeof(CedTextureManager));
    ct->textures = malloc(capacity * sizeof(CedTexture*));
    ct->hashes = malloc(capacity * sizeof(Hash));
    ct->capacity = capacity;
    ct->renderer = renderer;
    ct->size = 0;
}

void ced_texture_manager_free(CedTextureManager* ct){
    for (size_t i = 0; i < ct->size; i++)
    ced_texture_free(ct->textures[i]);
    free(ct->textures);
    free(ct->hashes);
    free(ct);
}

Hash ced_texture_manager_load(CedTextureManager* ct, const char* file)
{
    Hash h = hash(file);
    if (ced_texture_manager_get(ct, h)) return h;
    if (ct->size == ct->capacity){
        printf("[CRITICAL]: CedTexctures out of capacity!");
        exit(-1);
    }

    char path[256];
    sprintf(path, "textures/%s", file);
    ct->textures[ct->size] = IMG_LoadTexture(ct->renderer->renderer, path);      
    ct->hashes[ct->size] = h; 
    ct->size++;

    return h;
}

void ced_texture_manager_load_many(CedTextureManager* ct, const char* files[], size_t size){
    for (size_t i = 0; i < size ; i++)
        ced_texture_manager_load(ct, files[i]);
}

CedTexture* ced_texture_manager_get(const CedTextureManager* ct, Hash id){
    size_t i = 0;

    // Simple search. I know... but is OK for the prototype.
    while(i < ct->size){
        if (ct->hashes[i] == id) break;
        i++;
    }
    
    if(i >= ct->size) return NULL;
    return ct->textures[i];
}

CedTexture* ced_texture_manager_get_by_path(CedTextureManager* ct, const char* file){
    Hash id = ced_texture_manager_load(ct, file);
    return ced_texture_manager_get(ct, id);
}