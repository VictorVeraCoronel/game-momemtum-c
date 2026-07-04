#pragma once
#include "../../core/world.h"
#include <raylib.h>

void Camera_Update(World* world, Camera2D *camera, float dt);

void Camera_InitSystem(World* world, Camera2D *camera);
