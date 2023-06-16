#ifndef PLAYER_H
#define PLAYER_H

struct Motion {
	int speed; // horizontal and vertical velocity
	SDL_Rect dstrect; // player destination
}__attribute__((aligned(32)));

struct Texture {
	SDL_Texture* PlayerTex; // player texture
	SDL_RendererFlip flip; // player direction
	SDL_Rect srcrect; // player source from the player spritesheet
}__attribute__((aligned(32)));

struct Player {
	struct Motion motion;
	struct Texture texture;
}__attribute__((aligned(128)));

/* Physics */

/* Texture Rendering */

void FaceDirection(struct Player* player);

void SpriteAnimation(struct Player* player);

void RenderPlayer(SDL_Renderer* rend, struct Player player);

#endif // PLAYER_H
