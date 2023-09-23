#include "Game/Game.hpp"
#include "Scenes/ImageClassifier.hpp"
#include "Scenes/idxImageViewer.hpp"
#include "Test.hpp"

int main() {
	Game &game = Game::get();
	if (!game.init("settings.json")) return 1;

	game.addScene(std::make_unique<ImageClassifier>());

	game.run();

	//		run();
	//		run2();
	//		teachImages();
	//		trainImages();
}
