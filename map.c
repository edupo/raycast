#include <stdio.h>
#include <math.h>

#include "map.h"

Map* map_create(size_t width, size_t height, int* data){
    Map* m = (Map*) malloc(sizeof(Map));

    m->width = width; 
    m->height = height;
    m->lenght = width*height;
    m->data = (int*) malloc(sizeof(int) * m->lenght);

    for (int i = 0; i < m->lenght; i++) 
        m->data[i] = data[i];
    return m;
}

void map_free(Map* m){
    free(m->data);
    free(m);
}

int map_get(const Map* m, int x, int y){
    int i = x + m->width * y;
    if(i >= m->lenght)
        return -1;
    else
        return m->data[i];
}