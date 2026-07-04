#pragma once
#include "constants.h"
#include "components.h"
#include "custom_types.h"

typedef struct {
    //--------------------------------------------------
    // ENTITY CONTROL
    //--------------------------------------------------
    bool active_entities[MAX_ENTITIES];


    //--------------------------------------------------
    // BASE COMPONENTS
    //--------------------------------------------------
    Render renders[MAX_ENTITIES];
    Motion motions[MAX_ENTITIES];
    Locomotion locomotions[MAX_ENTITIES];
    Collider colliders[MAX_ENTITIES];
    Transform2D transforms[MAX_ENTITIES];
    AudioSource audio_sources[MAX_ENTITIES];
    Input inputs[MAX_ENTITIES];
    AI ais[MAX_ENTITIES];
    Animation animations[MAX_ENTITIES];
    Health healths[MAX_ENTITIES];


    //--------------------------------------------------
    // EVENT COMPONENTS
    //--------------------------------------------------
    ImpulseRequest impulse_requests[MAX_ENTITIES];
    TeleportRequest teleport_requests[MAX_ENTITIES];
    DamageRequest damage_requests[MAX_ENTITIES];


    //--------------------------------------------------
    // ASSET REPOSITORIES
    //--------------------------------------------------
    AssetRepository sprites[MAX_ASSETS];
    AssetRepository tiles[MAX_ASSETS];
    AssetRepository uis[MAX_ASSETS];
    AssetRepository wallpapers[MAX_ASSETS];


    //--------------------------------------------------
    // WORLD STATE AND SCREEN
    //--------------------------------------------------
    Level current_level;
    float gravity;


} World;
