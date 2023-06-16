#include "../level.h"
#include "../player/player.h"
#include "../scene/scene.h"
#include "../ground/ground.h"
#include "boundaries.h"

void SceneBoundaries(struct Scene* scene) {
    /* Scene boundaries */
    // left boundary
    if (scene->srcrect.x < 0) {
        scene->srcrect.x = 0;
	}
    // right boundary
    if (scene->srcrect.x > LEVEL_WIDTH - scene->srcrect.w) {
        scene->srcrect.x = LEVEL_WIDTH - scene->srcrect.w;
	}
    // bottom boundary
    if (scene->srcrect.y > LEVEL_WIDTH - scene->srcrect.h) {
        scene->srcrect.y = LEVEL_WIDTH - scene->srcrect.h;
	}
    // top boundary
    if (scene->srcrect.y < 0) {
        scene->srcrect.y = 0;
	}
}

void GroundBoundaries(struct Ground* ground) {
    /* Scene boundaries */
    // left boundary
    if (ground->srcrect.x < 0) {
        ground->srcrect.x = 0;
	}
    // right boundary
    if (ground->srcrect.x > LEVEL_WIDTH - ground->srcrect.w) {
        ground->srcrect.x = LEVEL_WIDTH - ground->srcrect.w;
	}
    // bottom boundary
    if (ground->srcrect.y > LEVEL_WIDTH - ground->srcrect.h) {
        ground->srcrect.y = LEVEL_WIDTH - ground->srcrect.h;
	}
    // top boundary
    if (ground->srcrect.y < 0) {
        ground->srcrect.y = 0;
	}
}

void PlayerBoundaries(struct Player* player, int screen_width) {
    /* Player boundaries */
    const int level_offset = LEVEL_WIDTH - screen_width - LEVEL_WIDTH/2; // level offset

    // left boundary
    if (player->motion.dstrect.x - player->motion.dstrect.w/2 < -(level_offset)) {
        player->motion.dstrect.x =-(level_offset) + player->motion.dstrect.w/2;
	}
    // right boundary
    if (player->motion.dstrect.x + player->motion.dstrect.w/2 > LEVEL_WIDTH + level_offset) {
        player->motion.dstrect.x = LEVEL_WIDTH + level_offset - player->motion.dstrect.w/2;
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
