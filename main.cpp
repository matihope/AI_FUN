#include "Game/Game.hpp"
#include "Scenes/IdxImageViewer.hpp"
#include "Scenes/ImageClassifierScene.hpp"
#include "Test.hpp"

int main() {
	Game &game = Game::get();
	if (!game.init("settings.json")) return 1;

	game.addScene(std::make_unique<ImageClassifierScene>());

	game.run();

	//		run();
	//		run2();
	//		teachImages();
	//		trainImages();
}
