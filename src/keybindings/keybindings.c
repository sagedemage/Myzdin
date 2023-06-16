#include "../player/player.h"
#include "keybindings.h"
#include <stdio.h>

bool ClickKeybindings(bool quit) {
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
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
                }
                break;

            case SDL_CONTROLLERBUTTONDOWN: // controller button press
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
    int down_dpad = SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    int up_dpad = SDL_GameControllerGetButton(gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_UP);

    if (state[SDL_SCANCODE_LEFT] == 1 || left_dpad == 1) { //left
        player->motion.dstrect.x -= player->motion.speed;
    }
    else if (state[SDL_SCANCODE_RIGHT] == 1 || right_dpad == 1) { //right
        player->motion.dstrect.x += player->motion.speed;
    }

    if (state[SDL_SCANCODE_UP] == 1 || up_dpad == 1) { //right
        player->motion.dstrect.y -= player->motion.speed;
    }
    else if (state[SDL_SCANCODE_DOWN] == 1 || down_dpad == 1) { //left
        player->motion.dstrect.y += player->motion.speed;
    }
}

