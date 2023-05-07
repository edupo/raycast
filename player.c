#include <stdlib.h>
#include "player.h"

Player* player_create(float x, float y, float angle, float speed){
    Player* p = (Player*) malloc(sizeof(Player));
    p->position.x = x;
    p->position.y = y;
    p->speed = speed;
    player_set_angle(p, angle);
    return p;
}

void player_free(Player* p){
    free(p);
}

void player_set_angle(Player* p, float angle){
    if( angle < 0 )  // Clamp angle from 0 to 2PI
        angle += C_2PI;
    else if ( angle > C_2PI )
        angle -= C_2PI;
    p->angle = angle;
    v2f_from_angle(&p->direction, angle);
}

void player_move_forward(Player* p){
    p->position.x += p->speed * p->direction.x;
    p->position.y += p->speed * p->direction.y;
}

void player_move_backwards(Player* p){
    p->position.x -= p->speed * p->direction.x;
    p->position.y -= p->speed * p->direction.y;
}
