#ifndef GROUND_H
#define GROUND_H

/* The srcrect displays a portion of the ground view */

struct Ground {
    SDL_Rect dstrect; // ground destination
	SDL_Rect srcrect; // portion of the ground source
	SDL_Texture* GroundTex; // scene
}__attribute__((aligned(64)));

void RenderGround(SDL_Renderer* rend, struct Ground ground);

#endif // GROUND_H
