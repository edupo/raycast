#pragma once

#include "types.h"
#include "renderer.h"

typedef struct {
    CedRenderer* renderer;
    CedTexture** textures;
    Hash* hashes;
    size_t size;
    size_t capacity;
} CedTextureManager;

void ced_texture_free(CedTexture* texture);

CedTextureManager* ced_texture_manager_create(CedRenderer* renderer, size_t capacity);
void ced_texture_manager_free(CedTextureManager* textures);

Hash ced_texture_manager_load(CedTextureManager* ced_textures, const char* file);
void ced_texture_manager_load_many(CedTextureManager* ced_textures, const char* files[], size_t n_files);
CedTexture* ced_texture_manager_get(const CedTextureManager* textures, Hash id);
CedTexture* ced_texture_manager_get_by_path(CedTextureManager* ced_textures, const char* file);
