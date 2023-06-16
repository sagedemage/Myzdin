#include "../player/player.h"
#include "../scene/scene.h"
#include "../ground/ground.h"
#include "../keybindings/keybindings.h"
#include "../boundaries/boundaries.h"
#include "../scrolling/scrolling.h"
#include "../collision/collision.h"
#include "game_play.h"

void GamePlay(SDL_Renderer* rend, struct Player player, struct Scene scene, struct Ground ground, SDL_GameController* gamecontroller, Mix_Chunk* landing_noise) {
	/* Implements the gameplay */
	bool quit = false; // gameplay loop switch
	const int second = 1000; // 1000 ms equals 1s
	const int gameplay_frames = 60; // amount of frames
	struct SceneCoords scene_coords = {0, 0}; // scene coordinates

	// Pointers
	struct Player* rplayer = &player;
	struct Scene* rscene = &scene;
	struct Ground* rground = &ground;

	#pragma unroll
	while(!quit) { // gameplay loop
		/* Keybindings */
		quit = ClickKeybindings(quit, rplayer); // Click

		HoldKeybindings(gamecontroller, rplayer); // Hold Keybindings

		/* Scrolling */
		SceneScrolling(rscene, player); // scene scrolling
		GroundScrolling(rground, player); // ground scrolling

		/* Animation */
		SpriteAnimation(rplayer); // sprite animation

		/* Movement */
		Gravity(rplayer); // gravity
		Inertia(rplayer); // inertia

		/* Facing Direction */
		FaceDirection(rplayer); // player sprite direction

		/* Collision */
		ground_collison(rplayer, ground); // Ground Collision
		collision_soundeffect(landing_noise, rplayer); // Collison soundeffect

		/* Boundaries */
		SceneBoundaries(rscene); // Set Camera Boundaries
		GroundBoundaries(rground); // Set Ground Boundaries
		PlayerBoundaries(rplayer, scene.srcrect.w); // Set Player Boundaries

		/* update scene coordinates */
		scene_coords.xpos = scene.srcrect.x;
		scene_coords.ypos = scene.srcrect.y;

		/* Rendering Frames */
		RenderScene(rend, scene); // Render scene
		RenderGround(rend, ground); // Render ground
		RenderPlayer(rend, player, scene_coords, scene.srcrect.w); // Render player
		SDL_RenderPresent(rend); // Triggers double buffers for multiple rendering
        SDL_Delay(second / gameplay_frames); // Calculates to 60 fps
	}
}

