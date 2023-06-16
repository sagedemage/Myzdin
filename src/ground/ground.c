#include "ground.h"

void RenderGround(SDL_Renderer* rend, struct Ground ground) {
    /* Render the ground */
    SDL_RenderCopy(rend, ground.GroundTex, &ground.srcrect, &ground.dstrect);
}
