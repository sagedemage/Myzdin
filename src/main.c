#include "level.h"
#include "player/player.h"
#include "scene/scene.h"
#include "ground/ground.h"
#include "game_play/game_play.h"

const int window_width = 750;
const int window_height = 500;
const int player_view_width = 300;
const int player_view_height = 200;
const int ground_height = 25;
const int ground_width = 1000;
const int player_width = 51;
const int player_height = 75;

const int accely = 1; // max veritical acceleration of the player
const int spdx = 5; // max horizontal speed of player
const int spdy = 18; // max vertical speed of player

int main() {
	/* Mixer */
	const int music_volume = 12;
	const int sound_effect_volume = 48;
	const int chunksize = 1024;

	/* Paths to the assets of the game */
	const char *scene_path = "assets/art/scene.png";
	const char *player_path = "assets/art/spritesheet.png";
	const char *ground_path = "assets/art/ground.png";
	const char *music_path = "assets/music/lost.ogg";
	const char *landing_noise_path = "assets/soundeffects/landing_noise.wav";

	/* Initialize SDL, window, audio, and renderer */
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER); // Initialize SDL library
	
	SDL_GameController* gamecontroller = SDL_GameControllerOpen(0); // Open Game Controller
	
	// Create window
	SDL_Window* win = SDL_CreateWindow("Myzdin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);

	// Set Fullscreen
	//SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, chunksize); // Initialize SDL mixer
	
	// Creates a renderer to render the images
	// * SDL_RENDERER_ACCELERATED starts the program using the GPU hardware
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	/* Loads images, music, and soundeffects */
	// Creates the asset that loads the image into main memory
	SDL_Surface* SceneSurf = IMG_Load(scene_path);
	SDL_Surface* PlayerSurf = IMG_Load(player_path);
	SDL_Surface* GroundSurf = IMG_Load(ground_path);
	Mix_Music* music = Mix_LoadMUS(music_path);
	Mix_Chunk* landing_noise = Mix_LoadWAV(landing_noise_path);

	// Loads image to our graphics hardware memory
	SDL_Texture* SceneTex = SDL_CreateTextureFromSurface(rend, SceneSurf);
	SDL_Texture* PlayerTex = SDL_CreateTextureFromSurface(rend, PlayerSurf);
	SDL_Texture* GroundTex = SDL_CreateTextureFromSurface(rend, GroundSurf);

	struct Limits limits = {accely, spdx, spdy};
	struct Motion motion = {0, 0, 0, 0, 0, {0, LEVEL_HEIGHT - player_height, player_width, player_height}};
	struct Texture texture = {PlayerTex, SDL_FLIP_NONE, {0, 0, player_width, player_height}};
	struct Player player = {motion, limits, texture};
	struct Scene scene = {{0, 0, player_view_width, player_view_height}, SceneTex};
	struct Ground ground = {{0, LEVEL_HEIGHT - ground_height, ground_width, ground_height},
		{0, 0, player_view_width, ground_height}, GroundTex
	};

	Mix_VolumeMusic(music_volume); // Adjust music volume
	Mix_Volume(1, sound_effect_volume); // set soundeffect volume
	Mix_PlayMusic(music, -1); // Start background music (-1 means infinity)

	GamePlay(rend, player, scene, ground, gamecontroller, landing_noise); // Start movement and physics
	
	/* Free resources and close SDL and SDL mixer */
	// Deallocate player and scene surfaces
	SDL_FreeSurface(PlayerSurf);
	SDL_FreeSurface(SceneSurf);
	SDL_FreeSurface(GroundSurf);

	// Free the music
	Mix_FreeMusic(music);
	Mix_FreeChunk(landing_noise);

	// Destroy scene and player textures
	SDL_DestroyTexture(SceneTex);
    SDL_DestroyTexture(PlayerTex);
	SDL_DestroyTexture(GroundTex);

	// Destroy renderer
	SDL_DestroyRenderer(rend);

	// Destroy window
	SDL_DestroyWindow(win);

	SDL_GameControllerClose(gamecontroller); // Close Game Controller
	Mix_CloseAudio(); // Close Audio
	SDL_Quit(); // Quit SDL subsystems	
		
	return 0;
}
