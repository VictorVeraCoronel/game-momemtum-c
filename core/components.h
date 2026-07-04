#pragma once
#include "enum_types.h"
#include "raylib.h"
#include <stdio.h>

//------------------------------------------
// BASE COMPONENTS
//------------------------------------------
typedef struct {
    Vector2 position;
    Vector2 scale;

} Transform2D;

typedef struct {
    Vector2 velocity;
    uint8_t mass;
    bool is_grounded;
    WallCollision wall_collision;

} Motion;

typedef struct{
    uint16_t jumping_force;
    uint16_t wall_jumping_force;
    uint16_t running_force;
    uint16_t air_movement_force;
    uint16_t knockback_force;


} Locomotion;

typedef struct {
    Rectangle rect;
    ColliderType type;

} Collider;

typedef struct {
    Rectangle source;
    uint16_t width;
    uint16_t height;
    uint8_t asset_id;

} Render;

typedef struct {
    float immune_timer;
    uint8_t current;
    uint8_t max;

} Health;

typedef struct {
    float volume;
    float pitch;
    bool play_trigger;
    uint8_t sound_id;

} AudioSource;

typedef struct {
    float horizontal_lock_timer;
    float coyote_timer;
    MoveIntent move_intent;
    bool jump_pressed;
    bool jump_released;
    bool run_pressed;

} Input;

typedef struct {
    float speed;
    int16_t aggro_range;
    AIState state;
    AIArchetype archetype;

} AI;

typedef struct {
    float timer;
    float speed;
    uint8_t n_frames;
    uint8_t current_frame;
    AnimState state;
    AnimDirection direction;

} Animation;

//------------------------------------------
// EVENT COMPONENTS
//------------------------------------------

typedef struct {
    Vector2 target_position;
    bool pending;

} TeleportRequest;

typedef struct {
    uint8_t amount;
    bool pending;

} DamageRequest;

typedef struct {
    Vector2 acceleration;
    bool pending;

} ImpulseRequest;
