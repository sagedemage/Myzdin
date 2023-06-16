#include "scene.h"

void RenderScene(SDL_Renderer* rend, struct Scene scene) {
	SDL_RenderCopy(rend, scene.SceneTex, &scene.srcrect, NULL); // render scene
}
