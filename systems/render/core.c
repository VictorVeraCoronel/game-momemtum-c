#include "core.h"
#include <math.h>
#include "raylib.h"


static void RenderMap(World* world, Camera2D* camera, const VirtualScreen* virtual_screen){
    Level* level = &world->current_level;

    // DETERMINE INITIAL COL AND INITIAL ROW (X, Y)
    const int initial_x = (fmaxf(0, ((int)(camera->target.x - 1500)))) / (int)TILE_SIZE;
    const int initial_y = (fmaxf(0, ((int)(camera->target.y - 1000)))) / (int)TILE_SIZE;

    // DETERMINE HOW MANY TILES CAN FIT IN THE SCREEN
    const int tiles_x = (virtual_screen->width / TILE_SIZE) + 20; // NUMBER OF TILES YOU SEE IN AXIS X
    const int tiles_y = (virtual_screen->height / TILE_SIZE) + 20; // NUMBER OF TILES YOU SEE IN AXIS Y

    // DETERMINE FINAL COL AND FINAL ROW (X, Y)
    const int end_x = fminf((int)level->width, initial_x + tiles_x);
    const int end_y = fminf((int)level->height, initial_y + tiles_y);


    // For now, this texture is loaded once, in the future, it will be variable inside the loop below
    Texture2D texture = world->tiles[0].asset;

    for (int y = initial_y; y < end_y; y++) {
        for (int x = initial_x; x < end_x; x++) {

            const int position_x = TILE_SIZE * x;
            const int position_y = TILE_SIZE * y;
            const int index = (y * level->width) + (x);


            // DRAW MAP WHEN IT EXISTS
            if(level->map[index] != 0){
                DrawTexture(texture, position_x, position_y, WHITE);
            }

        }
    }
}

static void RenderBackground(World* world, Camera2D* camera){
    const float background_x = camera->target.x * 0.2f;
    const float background_y = camera->target.y * 0.2f;

    for (int i = -1; i < 5; i++) {

        for(int j = -1; j < 5; j++){
            const float background_width = 3840.0f;
            const float background_height = 2160.0f;
            DrawTexture(world->wallpapers[0].asset, background_x + (i * background_width), background_y + (j * background_height), WHITE);
        }

    }
}

static void RenderEntities(World* world){

    const Transform2D* transforms = world->transforms;
    const Motion* motions = world->motions;
    const Render* renders = world->renders;
    const Animation* animations = world->animations;
    const bool* active = world->active_entities;
    const AssetRepository* sprites = world->sprites;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(!active[i]) continue;

        const Transform2D* transform = &transforms[i];
        const Motion* motion = &motions[i];
        const Animation* animation = &animations[i];
        const Render* render = &renders[i];
        float width_sign = 1.0f; // 1.0f = RIGHT, -1.0f = LEFT

        if (motion->velocity.x > 10.0f) {
            width_sign = 1.0f;
        }
        else if (motion->velocity.x < -10.0f) {
            width_sign = -1.0f;
        }
        // SI EL PERSONAJE NO SE MUEVE HORIZONTALMENTE... PERO ESTÁ EN LA PARED:
        else if (motion->wall_collision != WALL_NONE) {

            // Si la pared está a la DERECHA, el stickman debe mirar hacia la DERECHA (hacia el muro)
            if (motion->wall_collision == WALL_RIGHT) {
                width_sign = 1.0f;
            }
            // Si la pared está a la IZQUIERDA, el stickman debe mirar hacia la IZQUIERDA
            else if (motion->wall_collision == WALL_LEFT) {
                width_sign = -1.0f;
            }
        }


        float source_x = (float)animation->current_frame * render->width;
        float source_y = (float)animation->state * render->height;
        Rectangle source_rec = { source_x, source_y, (float)render->width * width_sign, (float)render->height };

        Texture2D texture = sprites[render->asset_id].asset;
        Rectangle dest_rec = { transform->position.x, transform->position.y, (float)render->width, (float)render->height };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(texture, source_rec, dest_rec, origin, 0.0f, WHITE);

    }


}

void RenderCore_Update(World* world, Camera2D* camera, const VirtualScreen* virtual_screen){

    // RENDER THE WORLD IN THE VIRTUAL TEXTURE                                               |
    BeginTextureMode(virtual_screen->target_render_texture);
    ClearBackground(RAYWHITE);

    BeginMode2D(*camera);

        RenderBackground(world, camera);
        RenderEntities(world);
        RenderMap(world, camera, virtual_screen);


    EndMode2D();

    EndTextureMode();


    //---------------------------------------------------------------------------------------
    // DRAW VIRTUAL TEXTURE IN THE MONITOR
    //---------------------------------------------------------------------------------------
    BeginDrawing();
        ClearBackground(BLACK);

        // CALCULATE DYNAMIC SCALE DEPENDING ON USER SCREEN RESOLUTION
        float scale = fminf((float)GetScreenWidth() / virtual_screen->width,
                            (float)GetScreenHeight() / virtual_screen->height);

        Rectangle origin_rec = { 0.0f, 0.0f, (float)virtual_screen->target_render_texture.texture.width, (float)- virtual_screen->target_render_texture.texture.height };
        Rectangle destination_rec = {
            ((float)GetScreenWidth() - ((float)virtual_screen->width * scale)) * 0.5f,
            ((float)GetScreenHeight() - ((float)virtual_screen->height * scale)) * 0.5f,
            (float)virtual_screen->width * scale,
            (float)virtual_screen->height * scale
        };
        Vector2 origin = {0,0};
        DrawTexturePro(
            virtual_screen->target_render_texture.texture,
            // ORIGIN: RAYLIB'S Y AXIS TEXTURE IS INVERTED BY OPENGL CONVENTION, THATS WHY WE USE (-)
            origin_rec,
            destination_rec,
            origin,
            0.0f,
            WHITE
        );




        //---------------------------------------------------------------------------------------
        // DEBUG CONSOLE PRINTS                                                                  |
        //---------------------------------------------------------------------------------------
        char pos_x[50];
        snprintf(pos_x, sizeof(pos_x), "Position_x: %.2f", world->transforms[0].position.x);
        char pos_y[50];
        snprintf(pos_y, sizeof(pos_y), "Position_y: %.2f", world->transforms[0].position.y);

        char hp[50];
        snprintf(hp, sizeof(hp), "HP: %.2f", (double)world->healths[0].current);

        DrawText(pos_x ,2, 990, 32, BLACK);
        DrawText(pos_y ,2, 1042, 32, BLACK);
        DrawText(hp ,2, 960, 32, BLACK);



    EndDrawing();


}


