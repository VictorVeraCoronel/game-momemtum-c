#include "camera.h"
#include <math.h>

void Camera_Update(World* world, Camera2D *camera, float dt){

    //We create a Lerp factor.
    const float follow_slower = 0.13f;
    const float lerp_factor = 1.0f - pow(follow_slower, dt);
    const Vector2 p_position = world->transforms[0].position;


    if((float)fabsf(p_position.x - camera->target.x) < 10.0f && (float)fabsf(p_position.y - camera->target.y) < 10.0f){
        camera->target = (Vector2){ camera->target.x , camera->target.y };

    }else{
        camera->target = (Vector2){ camera->target.x + (p_position.x - camera->target.x) * lerp_factor, camera->target.y + (p_position.y - camera->target.y) * lerp_factor };
    }

}

void Camera_InitSystem(World* world, Camera2D *camera){

    const Vector2* p_position = &world->transforms[0].position;

    camera->target = (Vector2){ p_position->x, p_position->y};
    camera->zoom = 0.66f;
    camera->offset = (Vector2){ 1920.0f/2-64, 1080.0f/2.33-64 };

}
