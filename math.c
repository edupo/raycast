#include "math.h"

const float C_PI = M_PI;
const float C_2PI = 2.0 * M_PI;
const float C_PI2 = M_PI / 2.0;
const float C_3PI2 = 3.0 * C_PI2;

const float C_D2R = C_PI/180.0;
const float C_R2D = 180.0/C_PI;

inline float deg2rad(float a){
    return a * C_D2R;
}

inline float rad2deg(float a){
    return a * C_R2D;
}