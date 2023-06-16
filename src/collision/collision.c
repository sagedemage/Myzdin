#include "../level.h"
#include "../player/player.h"

void collision_soundeffect(Mix_Chunk* landing_noise) {
    // Collison soundeffect
    Mix_PlayChannel(1, landing_noise, 0); // acceleration not changing quick enough
}


