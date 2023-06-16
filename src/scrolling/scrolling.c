#include "../player/player.h"
#include "../scene/scene.h"
#include "../ground/ground.h"

void SceneScrolling(struct Scene* scene, struct Player player) {
    // Scene scrolling depending on the player location
    scene->srcrect.x = (player.motion.dstrect.x + player.texture.srcrect.w / 2 ) - scene->srcrect.w / 2;
    //return scene;
}

void GroundScrolling(struct Ground* ground, struct Player player) {
    // Ground scrolling depending on the player location
    ground->srcrect.x = (player.motion.dstrect.x + player.texture.srcrect.w / 2 ) - ground->srcrect.w / 2;
}
