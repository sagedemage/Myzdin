#ifndef GAME_PLAY_H
#define GAME_PLAY_H

void GamePlay(SDL_Renderer* rend, struct Player player, struct Scene scene, struct Ground ground, SDL_GameController* gamecontroller, Mix_Chunk* landing_noise);

#endif // GAME_PLAY_H
