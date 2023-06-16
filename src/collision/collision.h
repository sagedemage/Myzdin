#ifndef COLLISION_H
#define COLLISION_H

void ground_collison(struct Player* player, struct Ground ground);
void collision_soundeffect(Mix_Chunk* landing_noise, struct Player* player);

#endif // COLLISION_H
