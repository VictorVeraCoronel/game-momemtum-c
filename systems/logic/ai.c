#include "ai.h"
#include "world_utils.h"
#include "math.h"
#include <raylib.h>

void AI_Update(World* world){

    // Useful data references
    bool* active = world->active_entities;
    Transform2D* transforms = world->transforms;
    Motion* motions = world->motions;
    Locomotion* locomotions = world->locomotions;
    AI* ais = world->ais;
    Collider* colliders = world->colliders;
    Level* level = &world->current_level;

    for (int i = MAX_PLAYERS; i < MAX_ENTITIES; i++) {
        if (!active[i]) continue; //Performance check

        // Useful data references
        Transform2D* transform = &transforms[i];
        AI* ai = &ais[i];
        Motion* motion = &motions[i];
        Locomotion* locomotion = &locomotions[i];
        Collider* collider = &colliders[i];

        // Useful consts
        const Vector2 ai_position = transform->position;
        const Vector2 ai_size = {collider->rect.width, collider->rect.height};
        const float ai_patrol_speed = (float)locomotion->running_force;

        // LOOK FOR NEAREST PLAYER TO ENTITY
        int16_t nearest_player = GetClosestPlayerIndex(world, ai_position);

        // IF THERE ARE NO PLAYERS, AI WILL NOT UPDATE
        if (nearest_player == -1) continue;

        Vector2 closest_player_position = transforms[nearest_player].position;

        switch (ai->state) {

            case AI_IDLE:{
                motion->velocity.x = 0.0f;
                motion->velocity.y = 0.0f;

                break;
            }

            case AI_PATROL:{

                float time = GetTime();
                int8_t force_sign = 1;

                // DECIDE DIRECTION OF MOVEMENT BASED ON TIME
                if(sin(time) > 0){
                    force_sign = 1;
                }else{
                    force_sign = -1;
                }

                float horizontal_acceleration = force_sign * ai_patrol_speed;
                Vector2 next_position;


                // CALCULATE WHICH WILL BE THE NEXT POSITION DEPENDING ON FORCE SIGN
                if(force_sign == 1) {
                    next_position.x = (ai_position.x + (ai_size.x*2));
                    next_position.y = (ai_position.y + ai_size.y);
                }

                if(force_sign == -1) {
                    next_position.x = (ai_position.x - (ai_size.x*1));
                    next_position.y = (ai_position.y + ai_size.y);
                }


                // AI BEHAVIOUR DEPENDING ON NEXT TILE
                int index = GetTileIndexAtPosition(next_position.x, next_position.y, level);
                if(level->map[index] != 0){
                    motion->velocity.x = horizontal_acceleration;
                    motion->velocity.y = 0.0f;
                }else{
                    motion->velocity.x = 0;
                    motion->velocity.y = 0;
                }


                break;
            }

            case AI_FOLLOW:{

                break;
            }

        }

    }

}
