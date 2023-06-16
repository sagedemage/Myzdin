#include "../level.h"
#include "../player/player.h"
#include "../scene/scene.h"
#include "boundaries.h"

void PlayerBoundaries(struct Player* player) {
    /* Player boundaries */
    //const int level_offset = LEVEL_WIDTH - screen_width - LEVEL_WIDTH/2; // level offset

    // 0 , 7

    // player->motion.dstrect.w/2

    // left boundary
    if (player->motion.dstrect.x < 0) {
        player->motion.dstrect.x = 0;
	}
    // right boundary
    if (player->motion.dstrect.x + player->motion.dstrect.w > LEVEL_WIDTH) {
        player->motion.dstrect.x = LEVEL_WIDTH - player->motion.dstrect.w;
	}
    // bottom boundary
    if (player->motion.dstrect.y + player->motion.dstrect.h > LEVEL_HEIGHT) {
        player->motion.dstrect.y = LEVEL_HEIGHT - player->motion.dstrect.h;
	}
    // top boundary
    if (player->motion.dstrect.y < 0) {
        player->motion.dstrect.y = 0;
	}
}
