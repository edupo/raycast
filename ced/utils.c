#define _USE_MATH_DEFINES
#include <math.h>

#include "utils.h"

const float C_PI = M_PI;
const float C_2PI = 2.0 * M_PI;
const float C_PI2 = M_PI / 2.0;
const float C_3PI2 = 3.0 * C_PI2;

const float C_D2R = C_PI/180.0;
const float C_R2D = 180.0/C_PI;

inline float deg2rad(float a)
{
    return a * C_D2R;
}

inline float rad2deg(float a)
{
    return a * C_R2D;
}

Hash hash(const char* str)
{
    // From https://stackoverflow.com/a/7666577/7450304
    Hash hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

inline float clamp_f32(float x, float a, float b)
{
    return (x < a) ? a : (x > b) ? b : x;
}

inline uint32_t clamp_u32(uint32_t x, uint32_t a, uint32_t b)
{
    return (x < a) ? a : (x > b) ? b : x;
}