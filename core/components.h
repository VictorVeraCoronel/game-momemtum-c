#pragma once
#include "enum_types.h"
#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 scale;

} Transform2D;

typedef struct {
    Vector2 velocity;
    Vector2 aceleration;
    uint8_t mass;

} Motion;

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
    uint8_t n_frames;
    uint8_t current_frame;
    AnimState state;
    AnimDirection direction;

} Animation;
