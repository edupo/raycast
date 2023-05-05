#include "vector.h"

inline V2f v2f_add(V2f a, V2f b){
    return (V2f){a.x + b.x, a.y + b.y};
}

inline V2f v2f_sub(V2f a, V2f b){
    return (V2f){a.x - b.x, a.y - b.y};
}

inline V2f v2f_mul(V2f a, float b){
    return (V2f){a.x * b, a.y * b};
}