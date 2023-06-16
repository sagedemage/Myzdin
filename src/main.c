#include "level.h"
#include "player/player.h"
#include "scene/scene.h"
#include "game_play/game_play.h"

// #define LEVEL_WIDTH 1000
const int window_width = 750;
const int window_height = 500;


const int player_view_width = 300;
const int player_view_height = 200;
const int ground_height = 25;
const int ground_width = 1000;
const int player_width = 50;
const int player_height = 50;

const int player_speed = 2; // speed of player

int main() {
	/* Mixer */
	const int music_volume = 12;
	const int sound_effect_volume = 48;
	const int chunksize = 1024;

	/* Paths to the assets of the game */
	const char *player_path = "assets/art/player.png";
	const char *music_path = "assets/music/lost.ogg";
	const char *landing_noise_path = "assets/soundeffects/landing_noise.wav";

	/* Initialize SDL, window, audio, and renderer */
	int sdl_status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER); // Initialize SDL library

	if (sdl_status == -1) {
		printf("Mix_OpenAudio: %s\n", SDL_GetError());
	}
	
	SDL_GameController* gamecontroller = SDL_GameControllerOpen(0); // Open Game Controller
	
	// Create window
	SDL_Window* win = SDL_CreateWindow("Myzdin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);

	// Set Fullscreen
	//SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	
    int open_audio_status = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, chunksize); // Initialize SDL mixer

	if (open_audio_status == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
	}
	
	// Creates a renderer to render the images
	// * SDL_RENDERER_ACCELERATED starts the program using the GPU hardware
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(rend, 134, 191, 255, 255);

	/* Loads images, music, and soundeffects */
	// Creates the asset that loads the image into main memory
	SDL_Surface* PlayerSurf = IMG_Load(player_path);
	Mix_Music* music = Mix_LoadMUS(music_path);
	Mix_Chunk* landing_noise = Mix_LoadWAV(landing_noise_path);

	// Loads image to our graphics hardware memory
	SDL_Texture* PlayerTex = SDL_CreateTextureFromSurface(rend, PlayerSurf);

	struct Motion motion = {player_speed, {0, LEVEL_HEIGHT - player_height, player_width, player_height}};
	struct Texture texture = {PlayerTex, {0, 0, player_width, player_height}};
	struct Player player = {motion, texture};

	Mix_VolumeMusic(music_volume); // Adjust music volume
	Mix_Volume(1, sound_effect_volume); // set soundeffect volume

	int player_music_status = Mix_PlayMusic(music, -1); // Start background music (-1 means infinity)

	if (player_music_status == -1) {
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}

	GamePlay(rend, player, gamecontroller); // Start movement and physics
	
	/* Free resources and close SDL and SDL mixer */
	// Deallocate player and scene surfaces
	SDL_FreeSurface(PlayerSurf);

	// Free the music
	Mix_FreeMusic(music);
	Mix_FreeChunk(landing_noise);

	// Destroy scene and player textures
    SDL_DestroyTexture(PlayerTex);

	// Destroy renderer
	SDL_DestroyRenderer(rend);

	// Destroy window
	SDL_DestroyWindow(win);

	SDL_GameControllerClose(gamecontroller); // Close Game Controller
	Mix_CloseAudio(); // Close Audio
	SDL_Quit(); // Quit SDL subsystems	
		
	return 0;
}
