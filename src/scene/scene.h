#ifndef SCENE_H
#define SCENE_H

/* 
The srcrect displays the scene view
and it displays a portion of the map
*/

struct Scene {
	SDL_Rect srcrect; // portion of the scene view
	SDL_Texture* SceneTex; // scene
}__attribute__((aligned(32)));

void RenderScene(SDL_Renderer* rend, struct Scene scene);

#endif // SCENE_H
