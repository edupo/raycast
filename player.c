#include <stdlib.h>
#include <math.h>

#include "player.h"
#include "config.h"

Player* player_create(V2f position, float angle){
    Player* p = (Player*) malloc(sizeof(Player));
    p->position = position;

    p->walk_speed = PLAYER_WALK_SPEED;
    p->run_speed = PLAYER_RUN_SPEED;
    p->rotation_speed = PLAYER_ROTATION_SPEED;

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
    p->direction = v2f_from_angle(angle);
}

void player_update(Player* p, float delta_time){
    float move_speed = (p->command.run) ? p->run_speed : p->walk_speed;
    float forward_speed = p->command.forward * move_speed * delta_time;
    float strafe_speed = p->command.strafe * move_speed * delta_time;
    float rotation_speed = p->command.rotation * p->rotation_speed * delta_time;
    if (fabsf(forward_speed) > 0.0001){
        p->position.x += p->direction.x * forward_speed;
        p->position.y += p->direction.y * forward_speed;
    }
    if (fabsf(strafe_speed) > 0.0001){
        p->position.x += p->direction.y * strafe_speed;
        p->position.y -= p->direction.x * strafe_speed;
    }
    if (fabsf(rotation_speed) > 0.01){
        player_set_angle(p, p->angle + rotation_speed);
    }
}
