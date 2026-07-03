#include "physics.h"

void Physics_Update(World* world, float dt){

    // Useful data references
    Transform2D* transforms = world->transforms;
    Motion* motions = world->motions;
    ImpulseRequest* impulses = world->impulse_requests;
    TeleportRequest* teleports = world->teleport_requests;
    bool* active  = world->active_entities;

    for(int i = 0; i < MAX_ENTITIES; i++){
        // Security check
        if(!active[i]) continue;

        // Local references
        Transform2D* transform = &transforms[i];
        Motion* motion = &motions[i];

        //-------------------------------------------------------------
        // EXTERNAL EVENTS (IMPULSES AND TELEPORTS)
        //-------------------------------------------------------------
        if(teleports[i].pending){

            transform->position.x = teleports[i].target_position.x;
            transform->position.y = teleports[i].target_position.y;

            motion->velocity.x = 0;
            motion->velocity.y = 0;

            teleports[i].pending = false;

            // If we teleport, we do not want to check the rest of physics in this frame.
            continue;
        }

        if(impulses[i].pending){

            motion->velocity.x += impulses[i].acceleration.x * dt;
            motion->velocity.y += impulses[i].acceleration.y * dt;

            impulses[i].pending = false;
        }



        //-------------------------------------------------------------
        // APPLY GRAVITY
        //-------------------------------------------------------------
        motion->velocity.y += world->gravity * dt;



    }

}
