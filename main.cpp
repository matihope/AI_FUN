#include "Game/Game.hpp"
#include "IdxDigitTrainer.hpp"
#include "Random/Random.hpp"
#include "Scenes/ImageClassifierScene.hpp"

#include <random>

int main() {
	//	IdxDigitTrainer::teachImages("newDigits.json");
	//	IdxDigitTrainer::testImages("newDigits.json");

	mk::Game &game = mk::Game::get();
	if (!game.init("settings.json")) return 1;

	game.addScene(std::make_unique<ImageClassifierScene>());

	game.run();
}
