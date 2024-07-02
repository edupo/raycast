#include "camera.h"

CedCamera* ced_camera_create(float fov){
    CedCamera* c = malloc(sizeof(CedCamera));
    c->fov = fov;
    return c;
}

void ced_camera_free(CedCamera* c){
    free(c);
}

void ced_camera_place(CedCamera* c, V2f pos, V2f dir){
    c->pos = pos;
    c->dir = dir;
    c->plane.x = dir.y;
    c->plane.y = -dir.x;
}
