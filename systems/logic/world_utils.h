#pragma once
#include "../../core/world.h"

uint16_t GetClosestPlayerIndex(const World* world, Vector2 entity_position);

uint16_t GetTileIndexAtPosition(float pixel_x, float pixel_y, Level* level);

int GetSignf(float val);

int GetOpositeSignf(float val);

void KillEnemy(World* world, int i);

void KillProjectile(World* world, int i);
