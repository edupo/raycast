#pragma once

#include "types.h"

extern const float C_PI;
extern const float C_2PI;
extern const float C_PI2;
extern const float C_3PI2;

extern const float C_D2R;
extern const float C_R2D;

float deg2rad(float a);
float rad2deg(float a);

Hash hash(const char* str);

float clamp_f32(float x, float a, float b);
uint32_t clamp_u32(uint32_t x, uint32_t min, uint32_t max);