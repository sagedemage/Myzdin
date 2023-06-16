#include "../level.h"
#include "../player/player.h"
#include "../ground/ground.h"

void ground_collison(struct Player* player, struct Ground ground) {
    // Calculate the player's bottom edge
    int bottomP = player->motion.dstrect.y + player->motion.dstrect.h;

    // Ground Collision
    if (bottomP >= LEVEL_HEIGHT - ground.srcrect.h) {
        player->motion.dstrect.y = LEVEL_HEIGHT - ground.srcrect.h - player->motion.dstrect.h;
        player->motion.accely = 0;
    }
}

void collision_soundeffect(Mix_Chunk* landing_noise, struct Player* player) {
    // Collison soundeffect
    if (player->motion.vy == -player->limits.spdy && player->motion.accely == player->limits.accely) { // issue: trippy landing noise
        Mix_PlayChannel(1, landing_noise, 0); // acceleration not changing quick enough
    }
}


