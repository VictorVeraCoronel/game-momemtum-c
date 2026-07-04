#include "map.h"
#include "raylib.h"
#include <math.h>

void RenderMap_Update(World* world, Camera2D* camera, const VirtualScreen* virtual_screen){
    Level* level = &world->current_level;

    // DETERMINE INITIAL COL AND INITIAL ROW (X, Y)
    int initial_x = (fmaxf(0, ((int)(camera->target.x - 1500)))) / (int)TILE_SIZE;
    int initial_y = (fmaxf(0, ((int)(camera->target.y - 1000)))) / (int)TILE_SIZE;

    // DETERMINE HOW MANY TILES CAN FIT IN THE SCREEN
    int tiles_x = (virtual_screen->width / TILE_SIZE) + 20; // NUMBER OF TILES YOU SEE IN AXIS X
    int tiles_y = (virtual_screen->height / TILE_SIZE) + 20; // NUMBER OF TILES YOU SEE IN AXIS Y

    // DETERMINE FINAL COL AND FINAL ROW (X, Y)
    int end_x = fminf((int)level->width, initial_x + tiles_x);
    int end_y = fminf((int)level->height, initial_y + tiles_y);


    // For now, this texture is loaded once, in the future, it will be variable inside the loop below
    Texture2D texture = world->tiles[0].asset;

    for (int y = initial_y; y < end_y; y++) {
        for (int x = initial_x; x < end_x; x++) {

            int position_x = TILE_SIZE * x;
            int position_y = TILE_SIZE * y;
            int index = (y * level->width) + (x);


            // DRAW MAP WHEN IT EXISTS
            if(level->map[index] != 0){
                DrawTexture(texture, position_x, position_y, WHITE);
            }

        }
    }

}
