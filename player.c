#include "player.h"

void player_init(Player* p, float x, float y, float angle, float speed){
    p->position = (V2f){x, y};
    p->speed = speed;
    player_set_angle(p, angle);
}

void player_set_angle(Player* p, float angle){
    if( angle < 0 )  // Clamp angle from 0 to 2PI
        p->angle = angle + C_2PI;
    else if ( angle > C_2PI )
        p->angle = angle - C_2PI;
    p->direction = (V2f) {cos(p->angle), -sin(p->angle)};
}

void player_move_forward(Player* p){
    p->position = v2f_add(p->position, v2f_mul(p->direction, p->speed)); 
}

void player_move_backwards(Player* p){
    p->position = v2f_sub(p->position, v2f_mul(p->direction, p->speed)); 
}
