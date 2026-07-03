#include "animation.h"

void Animation_Update(World* world, float dt){
    Animation* animations = world->animations;

    for (int i = 0; i < MAX_ENTITIES; i++) {
        // Security check
        if(!world->active_entities[i]) continue;

        // Useful data references
        Animation* entity_animation = &animations[i];


        // CHECK IF ENTITY CAN BE ANIMATED
        if (entity_animation->n_frames <= 1) continue;

        // ANIMATION BEHAVIOUR
        entity_animation->timer += dt;

        if (entity_animation->timer >= entity_animation->speed) {
            entity_animation->timer = 0.0f;
            entity_animation->current_frame++;

            // RESET ANIMATION IF WE REACH LAST FRAME
            if (entity_animation->current_frame >= entity_animation->n_frames) {
                entity_animation->current_frame = 0;
            }

        }

    }

}
