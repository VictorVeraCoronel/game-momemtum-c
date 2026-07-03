#include "./core/world.h"

#include "./systems/logic/physics.h"
#include "./systems/logic/gameplay.h"
#include "./systems/logic/input.h"
#include "./systems/logic/animation.h"
#include "systems/logic/ai.h"

#include "./systems/render/core.h"
#include "./systems/render/camera.h"

#include "core/custom_types.h"

#include "loaders/config.h"
#include "loaders/resource.h"

#include "raylib.h"
#include <stdlib.h>



void InitRaylibWindow(){
    InitWindow(800, 600, "MOMENTUM_C");
    //ToggleBorderlessWindowed();
    SetTargetFPS(144.0f);
}

int main(){

    // GRAPHIC INITIALIZATION
    InitRaylibWindow();
    Camera2D camera = {0, 0, 0, 0, 0, 0};
    //VirtualScreen virtual_screen = LoadVirtualScreen(1920, 1080, 1920, 1080);

    // LOGIC INITIALIZATION
    World* world = (World*) calloc(1, sizeof(World));
    if (world == NULL) return -1;//Security check

    VirtualScreen virtual_screen = {};

    RenderCamera_InitSystem(world, &camera);
    const float dt = 1.0f / 144.0f;
    float acumulador = 0.0f;


    // GAME LOOP
    while (!WindowShouldClose()) {

        // FIXED DELTA TIME SYNC
        float frame_time = GetFrameTime();
        if (frame_time > 0.25f) frame_time = 0.25f; //CLAMPING TO AVOID DEATH SPIRAL
        acumulador += frame_time;


        // FIXED LOGIC LOOP (144 HZ)
        while (acumulador >= dt) {
            Input_Update(world->inputs, dt);
            Animation_Update(world, dt);
            AI_Update(world);
            Gameplay_Update(world, dt);
            Physics_Update(world, dt);
            RenderCamera_Update(world, &camera, dt);


            acumulador -= dt;
        }

        // FRAME RENDER
        RenderCore_Update(world, &camera, virtual_screen);


    }


    CloseWindow();

    // Free all memory
    free(world);

    return 0;
}
