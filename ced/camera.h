#pragma once

#include "types.h"

typedef struct {
    float fov;
    V2f pos, dir; 
    V2f plane; 
} CedCamera;

CedCamera* ced_camera_create(float field_of_view_radians);
void ced_camera_free(CedCamera* camera);
void ced_camera_place(CedCamera* camera, V2f position, V2f direction);