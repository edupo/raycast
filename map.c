#include <stdio.h>
#include <math.h>

#include "map.h"

Map* map_create(size_t width, size_t height, int* data){
    Map* m = (Map*) malloc(sizeof(Map));

    m->width = width; 
    m->height = height;
    m->lenght = width*height;
    m->data = (int*) malloc(sizeof(int) * m->lenght);
    m->tile_size = TILE_SIZE;

    for (int i = 0; i < m->lenght; i++) 
        m->data[i] = data[i];
    return m;
}

void map_free(Map* m){
    free(m->data);
    free(m);
}

inline V2i map_point_to_coord(Map* m, V2f pos){
    return (V2i) {(int)floor(pos.x / m->tile_size), (int)floor(pos.y / m-> tile_size)};
}