#include <stdlib.h>

#include "camera.h"

Camera* camera_create(float fov){
    Camera* c = malloc(sizeof(Camera));
    c->fov = fov;
    return c;
}

void camera_free(Camera* c){
    free(c);
}

void camera_place(Camera* c, V2f pos, V2f dir){
    c->pos = pos;
    c->dir = dir;
    c->plane.x = dir.y;
    c->plane.y = -dir.x;
}
