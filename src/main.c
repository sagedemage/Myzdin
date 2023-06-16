#include "level.h"
#include "player/player.h"

const int window_width = 750;
const int window_height = 500;
const int player_view_width = 300;
const int player_view_height = 200;
const int ground_height = 25;
const int ground_width = 1000;
const int player_width = 50;
const int player_height = 50;
const int player_speed = 2;      // speed of player
const int second = 1000;         // 1000 ms equals 1s
const int gameplay_frames = 60;  // amount of frames
const int player_offset = 50;    // gap between left corner of the window

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
  int sdl_status = SDL_Init(SDL_INIT_VIDEO |
                            SDL_INIT_GAMECONTROLLER);  // Initialize SDL library

  if (sdl_status == -1) {
    printf("Mix_OpenAudio: %s\n", SDL_GetError());
  }

  SDL_GameController *gamecontroller =
      SDL_GameControllerOpen(0);  // Open Game Controller

  // Create window
  SDL_Window *win =
      SDL_CreateWindow("Myzdin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       window_width, window_height, 0);

  // Set Fullscreen
  // SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);

  int open_audio_status =
      Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2,
                    chunksize);  // Initialize SDL mixer

  if (open_audio_status == -1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
  }

  // Creates a renderer to render the images
  // * SDL_RENDERER_ACCELERATED starts the program using the GPU hardware
  SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(rend, 134, 191, 255, 255);

  /* Loads images, music, and soundeffects */
  // Creates the asset that loads the image into main memory
  SDL_Surface *PlayerSurf = IMG_Load(player_path);
  Mix_Music *music = Mix_LoadMUS(music_path);
  Mix_Chunk *landing_noise = Mix_LoadWAV(landing_noise_path);

  // Loads image to our graphics hardware memory
  SDL_Texture *PlayerTex = SDL_CreateTextureFromSurface(rend, PlayerSurf);

  struct Motion motion = {
      player_speed,
      {0 + player_offset, LEVEL_HEIGHT - player_height - player_offset,
       player_width, player_height}};
  struct Texture texture = {PlayerTex, {0, 0, player_width, player_height}};
  struct Player player = {motion, texture};

  Mix_VolumeMusic(music_volume);       // Adjust music volume
  Mix_Volume(1, sound_effect_volume);  // set soundeffect volume

  int player_music_status =
      Mix_PlayMusic(music, -1);  // Start background music (-1 means infinity)

  if (player_music_status == -1) {
    printf("Mix_PlayMusic: %s\n", Mix_GetError());
  }

  /* Gameplay Loop */
  // GamePlay(rend, player, gamecontroller); // Start movement and physics
  bool quit = false;  // gameplay loop switch

  // Player pointers
  // struct Player *rplayer = &player;

#pragma unroll
  while (!quit) {  // gameplay loop
    /* Keybindings */
    // quit = ClickKeybindings(quit); // Click

    /* Click Key Bindings */
    SDL_Event event;  // Event handling

#pragma unroll
    while (SDL_PollEvent(&event) == 1) {  // Events management
      switch (event.type) {
        case SDL_QUIT:  // close button
          quit = true;
          break;
        case SDL_KEYDOWN:  // key press
          if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            quit = true;
          }
          break;

        case SDL_CONTROLLERBUTTONDOWN:  // controller button press
          if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
            quit = true;
          }
        default:
          break;
      }
    }

    // HoldKeybindings(gamecontroller, rplayer); // Hold Keybindings

    /* Hold Keybindings */
    // Get the snapshot of the current state of the keyboard
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    int left_dpad = SDL_GameControllerGetButton(
        gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    int right_dpad = SDL_GameControllerGetButton(
        gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    int down_dpad = SDL_GameControllerGetButton(
        gamecontroller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    int up_dpad = SDL_GameControllerGetButton(gamecontroller,
                                              SDL_CONTROLLER_BUTTON_DPAD_UP);

    if (state[SDL_SCANCODE_LEFT] == 1 || left_dpad == 1) {  // move player left
      player.motion.dstrect.x -= player.motion.speed;
    } else if (state[SDL_SCANCODE_RIGHT] == 1 ||
               right_dpad == 1) {  // move player right
      player.motion.dstrect.x += player.motion.speed;
    }

    if (state[SDL_SCANCODE_UP] == 1 || up_dpad == 1) {  // move player up
      player.motion.dstrect.y -= player.motion.speed;
    } else if (state[SDL_SCANCODE_DOWN] == 1 ||
               down_dpad == 1) {  // move player down
      player.motion.dstrect.y += player.motion.speed;
    }

    /* Player boundaries */
    // left boundary
    if (player.motion.dstrect.x < 0) {
      player.motion.dstrect.x = 0;
    }
    // right boundary
    if (player.motion.dstrect.x + player.motion.dstrect.w > LEVEL_WIDTH) {
      player.motion.dstrect.x = LEVEL_WIDTH - player.motion.dstrect.w;
    }
    // bottom boundary
    if (player.motion.dstrect.y + player.motion.dstrect.h > LEVEL_HEIGHT) {
      player.motion.dstrect.y = LEVEL_HEIGHT - player.motion.dstrect.h;
    }
    // top boundary
    if (player.motion.dstrect.y < 0) {
      player.motion.dstrect.y = 0;
    }

    SDL_RenderClear(rend);

    SDL_RenderCopy(rend, player.texture.PlayerTex, &player.texture.srcrect,
                   &player.motion.dstrect);

    SDL_RenderPresent(rend);  // Triggers double buffers for multiple rendering
    SDL_Delay(second / gameplay_frames);  // Calculates to 60 fps
  }

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

  SDL_GameControllerClose(gamecontroller);  // Close Game Controller
  Mix_CloseAudio();                         // Close Audio
  SDL_Quit();                               // Quit SDL subsystems

  return 0;
}
