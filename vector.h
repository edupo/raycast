#pragma once

typedef struct {
    int x, y;
} V2i;

typedef struct {
    float x, y;
} V2f;

V2f v2f_add(V2f a, V2f b);
V2f v2f_sub(V2f a, V2f b);
V2f v2f_mul(V2f a, float b);
