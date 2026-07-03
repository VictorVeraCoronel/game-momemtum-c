#pragma once
#include "constants.h"
#include "raylib.h"
#include "enum_types.h"


typedef struct {
    uint8_t map[MAP_MAX_LENGTH];
    Vector2 respawn_point;
    uint16_t width;
    uint16_t height;

} Level;

// We will create 4 different asset arrays in the world, sprites, tiles, uis and wallpapers...
typedef struct {
    Texture2D asset;

} AssetRepository;

typedef struct {
    float anim_speed;
    float aggro_range;
    float patrol_speed;
    float follow_speed;

    uint16_t jumping_force;
    uint16_t running_force;
    uint16_t wall_jumping_force;
    uint16_t air_movement_force;
    uint16_t sprite_id;
    uint16_t sprite_width;
    uint16_t sprite_height;
    uint16_t width;
    uint16_t height;

    uint8_t mass;
    uint8_t n_animation_frames;
    uint8_t HP;
    uint8_t max_HP;
    AIArchetype ai_archetype; //uint8_t inside

} Entity;

typedef struct {
    // Middleman texture before rendering to real screen
    RenderTexture2D target_render_texture;

    uint16_t width;
    uint16_t height;

} VirtualScreen;
