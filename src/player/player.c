#include "player.h"

/* Physics */

void Gravity(struct Player* player) {
	/* Implements gravity */
	player->motion.dstrect.y -= player->motion.vy;
	if (player->motion.vy > -player->limits.spdy) {
		player->motion.vy -= player->motion.accely;
	}
	if (player->motion.vy == -player->limits.spdy) {
		/* when player is on the ground
		 * turn off jump initiation */
		player->motion.jump_init = false;
	}
}

void WalkSpeed(struct Player* player) {
	/* Set player speed */
	player->motion.move_stat = true;
	if (player->motion.vx == 0) {
		player->motion.move_stat = false;
	}
}

void Jump(struct Player* player) {
	/* Initiate player jump */
	if (player->motion.jump_init == false) {
		// jump if on the ground
		player->motion.jump_init = true;
		player->motion.vy = player->limits.spdy;
		player->motion.accely = player->limits.accely;
	}
}

void Inertia(struct Player* player) {
	/* The player's movement that depends on the player's speed */
	player->motion.dstrect.x += player->motion.vx;
}

/* Texture Rendering */

const int animation_frames = 200;

void FaceDirection(struct Player* player) {
	/* Face Direction */
	if (player->motion.vx < 0) {
		player->texture.flip = SDL_FLIP_HORIZONTAL;
	}
	if (player->motion.vx > 0) {
		player->texture.flip = SDL_FLIP_NONE;
	}
}

void SpriteAnimation(struct Player* player) {
	/* Sprite animaition of the player */
	Uint32 ticks = 0; // timer
	int seconds = 0; // seconds
	int sprite = 0; // sprite

	player->texture.srcrect.x = 0; // default sprite frame

	if (player->motion.move_stat == true && player->motion.jump_init == false) {
		/* walk animation */
		ticks = SDL_GetTicks(); // 1000 miliseconds
		seconds = (int) ticks / animation_frames; // 200 fps
		sprite = seconds % 4;
		player->texture.srcrect.x = sprite * player->texture.srcrect.w;
	}
	
	else if (player->motion.jump_init == true) {
		/* jump animation */
		player->texture.srcrect.x = player->texture.srcrect.w * 3;
	}
}

void RenderPlayer(SDL_Renderer* rend, struct Player player, struct SceneCoords scene_coords, int scene_width) {
	// Renders the player
	const int player_x_offset = 10;
	SDL_Rect incamera = {0, 0, player.texture.srcrect.w, player.texture.srcrect.h};
	incamera.x = (player.motion.dstrect.x + player.motion.dstrect.w - player_x_offset + scene_width/2) - scene_coords.xpos;
	incamera.y = player.motion.dstrect.y - scene_coords.ypos;
	SDL_RenderCopyEx(rend, player.texture.PlayerTex, &player.texture.srcrect, &incamera, 0.0, NULL, player.texture.flip);
}



