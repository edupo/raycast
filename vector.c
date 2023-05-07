#include <math.h>

#include "vector.h"

void v2f_from_angle(V2f* vector, float angle){
    vector->x = cos(angle);
    vector->y = -sin(angle);
}