#include "Game/Game.hpp"
#include "Scenes/IdxTestImgRecognition/IdxDigitTrainer.hpp"
#include "Scenes/MainMenu.hpp"

int main() {
	mk::Game &game = mk::Game::get();
	if (!game.init("settings.json")) return 1;

	game.addScene(std::make_unique<MainMenu>());

	game.run();
}
