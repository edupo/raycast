#pragma once

typedef struct {
    int x, y;
} V2i;

typedef struct {
    float x, y;
} V2f;

typedef struct {
    double x, y;
} V2d;

V2d v2d_from_angle(float angle);
V2f v2f_from_angle(float angle);