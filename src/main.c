#define LEVEL_WIDTH 750
#define LEVEL_HEIGHT 500

typedef struct Player {
    int speed;            /* horizontal and vertical velocity */
    SDL_Rect dstrect;     /* player destination */
    SDL_Texture *texture; /* player texture */
    SDL_Rect srcrect;     /* player source of texture */
} Player;

typedef enum { FALSE, TRUE } bool;

int main(void) {
    /* Player Attributes */
    const int player_width = 20;
    const int player_height = 20;
    const int player_speed = 2; /* speed of player */

    /* Frames per second */
    const int miliseconds = 1000;   /* 1000 ms equals 1s */
    const int gameplay_frames = 60; /* amount of frames per second */

    /* Mixer */
    const int music_volume = 12;
    const int chunksize = 1024;

    /* Paths to the assets of the game */
    const char *player_path = "assets/art/player.png";
    const char *music_path = "assets/music/lost.ogg";

    SDL_Window *win = NULL;
    SDL_Renderer *rend = NULL;
    bool quit = FALSE; /* gameplay loop switch */

    SDL_Surface *player_surf = NULL;
    Mix_Music *music = NULL;
    SDL_Texture *player_tex = NULL;

    const Uint8 *keyboard_state = NULL;

    Player player;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        return -1;
    }

    /* Create window */
    win =
        SDL_CreateWindow("Myzdin", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, LEVEL_WIDTH, LEVEL_HEIGHT, 0);

    /* Initialize SDL mixer */
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                      MIX_DEFAULT_CHANNELS, chunksize) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return -1;
    }

    /* Creates a renderer to render the images
     * - SDL_RENDERER_SOFTWARE starts the program using the CPU hardware
     * - SDL_RENDERER_ACCELERATED starts the program using the GPU hardware
     */
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(rend, 134, 191, 255, 255);

    /* Creates the asset that loads the image into main memory */
    player_surf = IMG_Load(player_path);
    music = Mix_LoadMUS(music_path);

    /* Loads image to our graphics hardware memory */
    player_tex = SDL_CreateTextureFromSurface(rend, player_surf);

    /* Set Player attributes */
    /** Motion **/
    player.speed = player_speed;
    player.dstrect.x = 0;
    player.dstrect.y = 0;
    player.dstrect.w = player_width;
    player.dstrect.h = player_height;

    /** Texture **/
    player.texture = player_tex;
    player.srcrect.x = 0;
    player.srcrect.y = 0;
    player.srcrect.w = player_width;
    player.srcrect.h = player_height;

    /* Adjust music volume */
    Mix_VolumeMusic(music_volume);

    /* Play music */
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
        return -1;
    }

    /* Gameplay Loop */
    while (quit == FALSE) {
        /* Click Key Bindings
         * - Event handling and management
         */
        SDL_Event event;
        while (SDL_PollEvent(&event) == 1) {
            switch (event.type) {
                case SDL_QUIT:
                    /* close button */
                    quit = TRUE;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        quit = TRUE;
                    }
                    break;
                default:
                    break;
            }
        }

        /* Hold Keybindings
         * - Get the snapshot of the current state of the keyboard
         */
        keyboard_state = SDL_GetKeyboardState(NULL);

        if (keyboard_state[SDL_SCANCODE_A] == 1) {
            /* move player left */
            player.dstrect.x -= player.speed;
        } else if (keyboard_state[SDL_SCANCODE_D] == 1) {
            /* move player right */
            player.dstrect.x += player.speed;
        } else if (keyboard_state[SDL_SCANCODE_W] == 1) {
            /* move player up */
            player.dstrect.y -= player.speed;
        } else if (keyboard_state[SDL_SCANCODE_S] == 1) {
            /* move player down */
            player.dstrect.y += player.speed;
        }

        /* Player boundaries */
        if (player.dstrect.x < 0) {
            /* left boundary */
            player.dstrect.x = 0;
        }
        if (player.dstrect.x + player.dstrect.w > LEVEL_WIDTH) {
            /* right boundary */
            player.dstrect.x = LEVEL_WIDTH - player.dstrect.w;
        }
        if (player.dstrect.y + player.dstrect.h > LEVEL_HEIGHT) {
            /* bottom boundary */
            player.dstrect.y = LEVEL_HEIGHT - player.dstrect.h;
        }
        if (player.dstrect.y < 0) {
            /* top boundary */
            player.dstrect.y = 0;
        }

        /* Update the screen with rendering */
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, player.texture, &player.srcrect, &player.dstrect);
        SDL_RenderPresent(
            rend); /* Triggers double buffers for multiple rendering */
        SDL_Delay(miliseconds / gameplay_frames); /* Calculates to 60 fps */
    }

    /* Free resources and close SDL and SDL mixer */
    /** Deallocate player and scene surfaces **/
    SDL_FreeSurface(player_surf);

    /** Free the music **/
    Mix_FreeMusic(music);

    /** Destroy scene and player textures **/
    SDL_DestroyTexture(player_tex);

    /** Destroy renderer **/
    SDL_DestroyRenderer(rend);

    /** Destroy window **/
    SDL_DestroyWindow(win);

    /** Close Mixer **/
    Mix_CloseAudio();

    /** Close SDL_image **/
    IMG_Quit();

    /** Quit SDL subsystems **/
    SDL_Quit();

    return 0;
}
