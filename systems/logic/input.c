#include "input.h"
#include <raylib.h>

void Input_Update(World* world, float dt){
    Input* inputs = world->inputs;

    for(int i = 0; i < MAX_PLAYERS; i++){
        // Security Check
        if(!world->active_entities[i]) continue;

        // Useful data references
        Input* p_input = &inputs[i];
        float* horizontal_lock = &inputs[i].horizontal_lock_timer;


        // RESET PREVIOUS FRAME INPUTS
        Input_Reset(p_input);

        // HORIZONTAL MOVEMENT
        if(*horizontal_lock > 0.0f){
            *horizontal_lock -= dt;
            p_input->move_intent = MOVE_NONE;
        }else{
            if(IsKeyDown(KEY_A)){
                p_input->move_intent = MOVE_LEFT;
            }
            else if(IsKeyDown(KEY_D)){
                p_input->move_intent = MOVE_RIGHT;
            }
        }

        // JUMP
        if(IsKeyPressed(KEY_SPACE)){
            p_input->jump_pressed = true;
        }
        if(IsKeyReleased(KEY_SPACE)){
            p_input->jump_released = true;
        }

        // RUNNING
        if(IsKeyDown(KEY_LEFT_SHIFT)){
            p_input->run_pressed = true;
        }

    }

}


void Input_Reset(Input* p_input){
    p_input->jump_pressed = false;
    p_input->jump_released = false;
    p_input->run_pressed = false;
    p_input->move_intent = MOVE_NONE;
}
