#include "Game/Game.hpp"

int main() {
	Game &game = Game::get();
	if (!game.init("settings.json")) return 1;
	game.run();
}
