#pragma once
#include "math.h"
#include "vector.h"

typedef struct{
    V2f position;
    V2f direction;
    float angle;
    float speed;
} Player;

Player* player_create(float x, float y, float angle, float speed);
void player_free(Player* p);
void player_set_angle(Player* p, float angle);
void player_move_forward(Player* p);
void player_move_backwards(Player* p);
