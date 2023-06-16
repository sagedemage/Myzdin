#include "player.h"

/* Physics */

/* Texture Rendering */

const int animation_frames = 200;

void FaceDirection(struct Player* player) {
	/* Face Direction */
	if (player->motion.speed < 0) {
		player->texture.flip = SDL_FLIP_HORIZONTAL;
	}
	if (player->motion.speed > 0) {
		player->texture.flip = SDL_FLIP_NONE;
	}
}

/*
void RenderPlayer(SDL_Renderer* rend, struct Player player) {
	// Renders the player
	//const int player_x_offset = 10;
	SDL_Rect incamera = {0, 0, player.texture.srcrect.w, player.texture.srcrect.h};
	//incamera.x = (player.motion.dstrect.x + player.motion.dstrect.w - player_x_offset + scene_width/2) - scene_coords.xpos;
	//incamera.y = player.motion.dstrect.y - scene_coords.ypos;
	SDL_RenderCopyEx(rend, player.texture.PlayerTex, &player.texture.srcrect, &incamera, 0.0, NULL, player.texture.flip);
}
*/



