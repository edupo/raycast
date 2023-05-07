#pragma once

typedef struct {
    int x, y;
} V2i;

typedef struct {
    float x, y;
} V2f;

void v2f_from_angle(V2f* vector, float angle);