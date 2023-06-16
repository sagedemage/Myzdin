#include "../player/player.h"
#include "keybindings.h"
#include <stdio.h>

bool ClickKeybindings(bool quit, struct Player* player) {
    /* Click Key Bindings */

    SDL_Event event; // Event handling
    //struct ClickKeys click_keys = {quit, motion};

    #pragma unroll
    while (SDL_PollEvent(&event) == 1) { // Events management
        switch(event.type) {
		    case SDL_QUIT: // close button
                quit = true;
                break;
            case SDL_KEYDOWN: // key press
                if (event.key.keysym.scancode == SDL_SCANCODE_K && event.key.repeat == 0) {
                    Jump(player);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
                }
                break;

            case SDL_CONTROLLERBUTTONDOWN: // controller button press
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
                    Jump(player);
                }
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                    quit = true;
                }
            default:
                break;
        }
    }
    return quit;
}

void HoldKeybindings(SDL_GameController* gamecontroller, struct Player* player) {
    /* Hold Key bindings */
    // Get the snapshot of the current state of the keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);

	int left_dpad = SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	int right_dpad = SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    player->motion.vx = 0;

    if (state[SDL_SCANCODE_A] == 1 || left_dpad == 1) { //left
		player->motion.vx = -player->limits.spdx;
    }

    if (state[SDL_SCANCODE_D] == 1 || right_dpad == 1) { //right
		player->motion.vx = player->limits.spdx;
    }

    WalkSpeed(player);
}

