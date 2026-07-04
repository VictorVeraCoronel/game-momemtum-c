#include "physics.h"
#include "world_utils.h"
#include <math.h>

void Physics_Update(World* world, float dt){

    // Useful data references
    Transform2D* transforms = world->transforms;
    Motion* motions = world->motions;
    Collider* colliders = world->colliders;
    Input* inputs = world->inputs;
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

            // Clear teleport request values
            motion->velocity.x = 0;
            motion->velocity.y = 0;
            teleports[i].target_position.x = 0;
            teleports[i].target_position.y = 0;
            teleports[i].pending = false;

            // If we teleport, we do not want to check the rest of physics in this frame.
            continue;
        }

        if(impulses[i].pending){

            motion->velocity.x += impulses[i].acceleration.x * dt;
            motion->velocity.y += impulses[i].acceleration.y * dt;

            // Clear impulse request values
            impulses[i].acceleration.x = 0;
            impulses[i].acceleration.y = 0;
            impulses[i].pending = false;
        }



        //-------------------------------------------------------------
        // APPLY GRAVITY
        //-------------------------------------------------------------
        motion->velocity.y += world->gravity * dt;



        //-------------------------------------------------------------
        // X TILEMAP COLLISIONS
        //-------------------------------------------------------------
        Collider* collider = &colliders[i];

        // Data references
        const float vel_x = motion->velocity.x;
        Level* level = &world->current_level;
        const float pos_x = transform->position.x;
        const float pos_y = transform->position.y;
        const float size_x = collider->rect.width;
        const float size_y = collider->rect.height;
        const float next_pos_x = pos_x + (vel_x * dt);
        bool collision_x = false;
        WallCollision wall_collision = WALL_NONE;

        //CHECK COLLISIONS WHEN MOVING RIGHT
        if(vel_x > 0){
            uint16_t index_top = GetTileIndexAtPosition((next_pos_x + size_x -1), pos_y, level);
            uint16_t index_bottom = GetTileIndexAtPosition((next_pos_x + size_x -1), (pos_y + size_y -1), level);

            if (level->map[index_top] > 0 || level->map[index_bottom] > 0){
                collision_x = true;
                wall_collision = WALL_RIGHT;
            }
        }


        // CHECK COLLISIONS WHEN MOVING LEFT
        if(vel_x < 0){
            uint16_t index_top =  GetTileIndexAtPosition(next_pos_x, pos_y, level);
            uint16_t index_bottom = GetTileIndexAtPosition(next_pos_x, (pos_y + size_y -1), level);

            if (level->map[index_top] > 0 || level->map[index_bottom] > 0){
                collision_x = true;
                wall_collision = WALL_LEFT;
            }
        }


        bool is_grounded = motion->is_grounded;
        const float vel_y = motion->velocity.y;
        // RESOLVE BEHAVIOUR DEPENDING ON RESULTS
        if (collision_x) {
            motion->velocity.x = 0.0f;// Halt X movement

            if (!is_grounded && vel_y > 0.0f) {
                motion->wall_collision = wall_collision;
            }else{
                motion->wall_collision = WALL_NONE;
            }

        }
        else {
            // Just move
            transform->position.x = next_pos_x;
            motion->wall_collision = WALL_NONE;
        }



        //-------------------------------------------------------------
        // Y TILEMAP COLLISIONS
        //-------------------------------------------------------------
        const float next_pos_y = pos_y + (vel_y * dt);
        bool collision_y = false;
        Input* input = &inputs[i];


        // CHECK COLLISIONS WHEN FALLING
        if (vel_y > 0) {
            int index_left = GetTileIndexAtPosition(pos_x, (next_pos_y + size_y), level);
            int index_right = GetTileIndexAtPosition((pos_x + size_x - 1),(next_pos_y + size_y), level);

            if (level->map[index_left] > 0 || level->map[index_right] > 0){
                int tile_row = (int)((next_pos_y + size_y) / TILE_SIZE);
                transform->position.y = (tile_row * TILE_SIZE) - size_y;


                collision_y = true;
                is_grounded = true;
                input->coyote_timer = 0.08f;
            }

        }

        //CHECK COLLISION WHEN JUMPING
        else if (vel_y < 0) {
            int index_left  = GetTileIndexAtPosition(pos_x , next_pos_y, level);
            int index_right =  GetTileIndexAtPosition((pos_x + size_x - 1), (next_pos_y), level);

            if (level->map[index_left] > 0 || level->map[index_right] > 0) collision_y = true;
        }


        // RESOLVE BEHAVIOUR DEPENDING ON RESULTS
        if (collision_y) {
            motion->velocity.y = 0.0f;// Halt Y movement
        }
        else {
            // Just move
            transform->position.y = next_pos_y;
            motion->is_grounded = false;
        }



        //-------------------------------------------------------------
        // APPLY FRICTIONS
        //-------------------------------------------------------------
        if(is_grounded){
            motion->velocity.x *= powf(GROUND_FRICTION, dt * 60.0f);

        }else if(motion->wall_collision != WALL_NONE){
            motion->velocity.x *= powf(WALL_FRICTION, dt * 60.0f);

        }
        else{
            motion->velocity.x *=  powf(AIR_FRICTION, dt * 60.0f);
        }


    }



    //-------------------------------------------------------------
    // PLAYER AND ENEMY COLLISIONS
    //-------------------------------------------------------------
    DamageRequest* damage_requests = world->damage_requests;
    Locomotion* locomotions = world->locomotions;
    Health* healths = world->healths;


    for(int i = 0; i < MAX_PLAYERS; i++){
        if (!active[i]) continue;

        for(int j = MAX_PLAYERS; j < MAX_ENTITIES; j++){
            if (!active[j]) continue;

            // Useful references
            const Vector2 player_pos = transforms[i].position;
            const Vector2 player_size = {colliders[i].rect.width, colliders[i].rect.height};
            const Vector2 player_vel = motions[i].velocity;
            const uint16_t player_jumping_force = locomotions[i].jumping_force;
            const Vector2 enemy_pos = transforms[j].position;
            const Vector2 enemy_size = {colliders[j].rect.width, colliders[j].rect.height};
            const uint16_t enemy_knockback_force = locomotions[j].knockback_force;

            // Update rectangle positions
            Rectangle player_rec = colliders[i].rect;
            player_rec.x = player_pos.x;
            player_rec.y = player_pos.y;

            Rectangle enemy_rec = colliders[j].rect;
            enemy_rec.x = enemy_pos.x;
            enemy_rec.y = enemy_pos.y;

            if(player_vel.y > 0.0f){

                float offset = 6.0f;
                bool jumping_on_head = (player_pos.y + player_size.y) < (enemy_pos.y + offset);
                bool collision_detected = CheckCollisionRecs(player_rec, enemy_rec);

                if(jumping_on_head && collision_detected && damage_requests[j].amount == 0){
                    damage_requests[j].amount += 1;
                    healths[i].immune_timer = 0.2f;
                    motions[i].velocity.y = player_jumping_force * (-1);

                }else if (collision_detected){
                    damage_requests[i].amount += 1;
                    motions[i].velocity.y = enemy_knockback_force * GetOpositeSignf(motions[i].velocity.y);
                    motions[i].velocity.x = enemy_knockback_force * GetOpositeSignf(motions[i].velocity.x);
                }

            }
            else{
                bool collision_detected = CheckCollisionRecs(player_rec, enemy_rec);

                if(collision_detected){
                    damage_requests[i].amount += 1;
                    motions[i].velocity.y = enemy_knockback_force * GetOpositeSignf(motions[i].velocity.y);
                    motions[i].velocity.x = enemy_knockback_force * GetOpositeSignf(motions[i].velocity.x);
                }
            }


        }
    }



}
