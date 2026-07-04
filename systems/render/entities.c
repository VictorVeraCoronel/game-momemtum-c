#include "entities.h"

void RenderEntities_Update(World* world){

    Transform2D* transforms = world->transforms;
    Motion* motions = world->motions;
    Render* renders = world->renders;
    Animation* animations = world->animations;
    bool* active = world->active_entities;
    AssetRepository* sprites = world->sprites;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(!active[i]) continue;

        Transform2D* transform = &transforms[i];
        Motion* motion = &motions[i];
        Animation* animation = &animations[i];
        Render* render = &renders[i];
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
        float source_y = (float)animation->state * renders->height;
        Rectangle source_rec = { source_x, source_y, (float)render->width * width_sign, (float)renders->height };

        Texture2D texture = sprites[render->asset_id].asset;
        Rectangle dest_rec = { transform->position.x, transform->position.y, (float)render->width, (float)render->height };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(texture, source_rec, dest_rec, origin, 0.0f, WHITE);

    }


}
