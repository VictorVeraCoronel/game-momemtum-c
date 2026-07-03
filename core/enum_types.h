#pragma once
#include <stdint.h>

typedef enum : uint8_t {
    COLLIDER_SOLID = 0,
    COLLIDER_TRIGGER = 1

} ColliderType;

typedef enum : uint8_t {
    MOVE_NONE = 0,
    MOVE_LEFT = 1,
    MOVE_RIGHT = 2

} MoveIntent;

typedef enum : uint8_t {
    WALL_NONE = 0,
    WALL_LEFT = 1,
    WALL_RIGHT = 2

} WallCollision;

typedef enum : uint8_t {
    AI_IDLE = 0,
    AI_PATROL = 1,
    AI_FOLLOW = 2

} AIState;

typedef enum : uint8_t {
    ARCHETYPE_MELEE = 0,
    ARCHETYPE_RANGED = 1,
    ARCHETYPE_PATROLLER = 2

} AIArchetype ;

typedef enum : uint8_t {
    ANIM_IDLE = 0,
    ANIM_RUNNING = 1,
    ANIM_JUMPING = 2,
    ANIM_FALLING = 3,
    ANIM_ATTACKING = 4,
    ANIM_DYING = 5,
    ANIM_WALL_SLIDING = 6,
    ANIM_CROUCH = 7,
    ANIM_HURT = 8

} AnimState;

typedef enum : uint8_t {
    DIR_LEFT = 0,
    DIR_RIGHT = 1

} AnimDirection;
