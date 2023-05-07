#include <math.h>

#include "vector.h"

inline V2d v2d_from_angle(float angle){
    return (V2d){cos(angle), -sin(angle)};
}
inline V2f v2f_from_angle(float angle){
    return (V2f){cosf(angle), -sinf(angle)};
}