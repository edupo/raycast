#pragma once

#include <math.h>

#include "vector.h"
#include "Map.h"

typedef struct {
    float fov;
    V2f pos, dir; 
    V2f plane; 
} Camera;

Camera* camera_create(float field_of_view_radians);
void camera_free(Camera* camera);
void camera_place(Camera* camera, V2f position, V2f direction);