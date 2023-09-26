#include "Game/Game.hpp"
#include "IdxDigitTrainer.hpp"
#include "Scenes/MainMenu.hpp"

int main() {
	//	IdxDigitTrainer::teachImagesAugmented("digitsAugmented.json");
	//	IdxDigitTrainer::testImages("digitsAugmented.json");
	mk::Game &game = mk::Game::get();
	if (!game.init("settings.json")) return 1;

	game.addScene(std::make_unique<MainMenu>());

	game.run();
}
