#include "world_utils.h"

uint16_t GetClosestPlayerIndex(const World* world, Vector2 entity_position){
    float min_distance_squared = 99999999.0f;
    int closest_player_index = -1;

    // Iterate through players (maximun of 5) and obtain the shortest distance
    for (int p = 0; p < MAX_PLAYERS; p++) {
        if (!world->active_entities[p]) continue; // Only iterate active players

        const Vector2 player_position = world->transforms[p].position;
        const float dx = player_position.x - entity_position.x;
        const float dy = player_position.y - entity_position.y;
        const float dist_sq = (dx * dx) + (dy * dy);// The real formula is Pythagoras using sqrt. We are not using sqrt to increase performance.

        if (dist_sq < min_distance_squared) {
            min_distance_squared = dist_sq;
            closest_player_index = p;
        }
    }

    return closest_player_index;
}

uint16_t GetTileIndexAtPosition(float pixel_x, float pixel_y, Level* level) {

    // Negative pixels are out of bounds
    if (pixel_x < 0.0f || pixel_y < 0.0f) return 0;

    // We determine tile cells using the pixels and tile size
    const int cell_x = (int)(pixel_x) / TILE_SIZE;
    const int cell_y = (int)(pixel_y) / TILE_SIZE;
    const int width = level->width;
    const int height = level->height;

    // Security check for out of bounds
    if (cell_x >= width || cell_y >= height) {
        return 0;
    }

    // Calculate index of the map
    return ((cell_y * width) + cell_x);
}

int GetSignf(float val) {
    return (val > 0.0f) - (val < 0.0f);
}

int GetOpositeSignf(float val){
    return -((val > 0.0f) - (val < 0.0f));
}


void KillEnemy(World* world, int i);

void KillProjectile(World* world, int i);
