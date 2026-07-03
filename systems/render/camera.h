#pragma once
#include "../../core/world.h"
#include <raylib.h>

void RenderCamera_Update(World* world, Camera2D *camera, float dt);

void RenderCamera_InitSystem(World* world, Camera2D *camera);
