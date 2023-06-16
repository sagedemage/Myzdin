#include "../player/player.h"
#include "../scene/scene.h"
#include "../keybindings/keybindings.h"
#include "../boundaries/boundaries.h"
#include "../collision/collision.h"
#include "game_play.h"

void GamePlay(SDL_Renderer* rend, struct Player player, SDL_GameController* gamecontroller) {
	/* Implements the gameplay */
	bool quit = false; // gameplay loop switch
	const int second = 1000; // 1000 ms equals 1s
	const int gameplay_frames = 60; // amount of frames

	// Pointers
	struct Player* rplayer = &player;

	#pragma unroll
	while(!quit) { // gameplay loop
		/* Keybindings */
		quit = ClickKeybindings(quit); // Click

		HoldKeybindings(gamecontroller, rplayer); // Hold Keybindings

		/* Boundaries */
		PlayerBoundaries(rplayer); // Set Player Boundaries

		SDL_RenderClear(rend);

		SDL_RenderCopy(rend, player.texture.PlayerTex, &player.texture.srcrect, &player.motion.dstrect);
		
		SDL_RenderPresent(rend); // Triggers double buffers for multiple rendering
        SDL_Delay(second / gameplay_frames); // Calculates to 60 fps
	}
}

