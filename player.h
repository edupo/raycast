#pragma once
#include "math.h"
#include "vector.h"

typedef struct{
    float forward;
    float rotation;
    float strafe;
    int run;
    int action;
} Command;

typedef struct{
    V2f position;
    V2f direction;
    float angle;

    float walk_speed;
    float run_speed;
    float rotation_speed;

    Command command;
} Player;

Player* player_create(V2f position, float angle);
void player_free(Player* p);
void player_set_angle(Player* p, float angle);
void player_update(Player* p, float delta_time);
