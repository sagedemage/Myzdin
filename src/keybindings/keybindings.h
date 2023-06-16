#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

struct ClickKeys {
	bool quit;
	struct Motion motion;
}__attribute__((aligned(128)));

bool ClickKeybindings(bool quit);
void HoldKeybindings(SDL_GameController* gamecontroller, struct Player* player);

#endif //KEYBINDINGS_H
