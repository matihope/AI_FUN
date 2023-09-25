#include "Game/Game.hpp"
#include "IdxDigitTrainer.hpp"
#include "Random/Random.hpp"
#include "Scenes/MainMenu.hpp"
#include "Scenes/MnistTestImgRecognition/ImageClassifierScene.hpp"

#include <random>

int main() {
	mk::Game &game = mk::Game::get();
	if (!game.init("settings.json")) return 1;

	game.addScene(std::make_unique<MainMenu>());

	game.run();
}
