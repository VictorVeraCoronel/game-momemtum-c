#pragma once
#include <stdint.h>

#define MAX_ENTITIES 500
#define MAX_PLAYERS 5
#define MAX_ASSETS 100
#define MAX_DATA 100
#define GROUND_FRICTION 0.85f
#define WALL_FRICTION 0.8f
#define AIR_FRICTION 0.98f
#define TILE_SIZE 64

#define MAX_MAX_HEIGHT 100
#define MAP_MAX_WIDTH 300
#define MAP_MAX_LENGTH (MAX_MAX_HEIGHT * MAP_MAX_WIDTH)

// Banderas de componentes (puedes ponerlo en constants.h o components.h)
typedef enum : uint16_t {
    COMP_NONE      = 0,
    COMP_TRANSFORM = 1 << 0,    // 0000000000000001
    COMP_MOTION    = 1 << 1,    // 0000000000000010
    COMP_COLLIDER  = 1 << 2,    // 0000000000000100
    COMP_RENDER    = 1 << 3,    // 0000000000001000
    COMP_HEALTH    = 1 << 4,    // 0000000000010000
    COMP_AUDIO     = 1 << 5,    // 0000000000100000
    COMP_INPUT     = 1 << 6,    // 0000000000100000
    COMP_AI        = 1 << 7,    // 0000000001000000
    COMP_ANIMATION = 1 << 8     // 0000000010000000
} ComponentMask;
