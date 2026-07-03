#pragma once
#include "constants.h"
#include "components.h"
#include "custom_types.h"

typedef struct {

    // ENTITY CONTROL

    //--------------------------------------------------
    // COMPONENTS
    //--------------------------------------------------
    Render renders[MAX_ENTITIES];
    Motion motions[MAX_ENTITIES];
    Collider colliders[MAX_ENTITIES];
    Transform2D transforms[MAX_ENTITIES];
    AudioSource audio_sources[MAX_ENTITIES];
    Input inputs[MAX_ENTITIES];
    AI ais[MAX_ENTITIES];
    Animation animations[MAX_ENTITIES];
    Health healths[MAX_ENTITIES];

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


} World;
