#ifndef PLAYER_H
#define PLAYER_H

struct Limits {
	const int accely;
	const int spdx;
	const int spdy;
}__attribute__((aligned(16)));

struct Motion {
	int accely; // acceleration
	int vx, vy; // horizontal and vertical velocity
	bool move_stat; // player movement status
	bool jump_init; // initiate jump
	SDL_Rect dstrect; // player destination
}__attribute__((aligned(32)));

struct Texture {
	SDL_Texture* PlayerTex; // player texture
	SDL_RendererFlip flip; // player direction
	SDL_Rect srcrect; // player source from the player spritesheet
}__attribute__((aligned(32)));

struct SceneCoords {
	int xpos;
	int ypos;
} __attribute__((aligned(8)));

struct Player {
	struct Motion motion;
	struct Limits limits;
	struct Texture texture;
}__attribute__((aligned(128)));

/* Physics */

void Gravity(struct Player* player);

void WalkSpeed(struct Player* player);

void Jump(struct Player* player);

void Inertia(struct Player* player);

/* Texture Rendering */

void FaceDirection(struct Player* player);

void SpriteAnimation(struct Player* player);

void RenderPlayer(SDL_Renderer* rend, struct Player player, struct SceneCoords scene_coords, int scene_width);

#endif // PLAYER_H
