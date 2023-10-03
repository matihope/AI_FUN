//
// Created by mateusz on 9/25/23.
//

#include "MainMenu.hpp"

#include "Game/Game.hpp"
#include "Scenes/DigitDrawing/DrawBoard.hpp"
#include "Scenes/FlappyBird/FlappyLevel.hpp"
#include "Scenes/IdxTestImgRecognition/ImageClassifierScene.hpp"
#include "Scenes/IdxTestImgRecognition/TestImageTransitions.hpp"

MainMenu::MainMenu() {
	auto font = mk::Game::get().getFont();

	float minBuffer = 5;

	recognize = addChild<mk::GUI::Button>(font, "View test images");
	recognize->setAlignment(
		mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::CENTER
	);
	recognize->setMinSize({ 333, -1 });
	recognize->setMinSpaceBetween({ minBuffer, minBuffer });
	recognize->setPosition(400, 400);

	draw = addChild<mk::GUI::Button>(font, "Draw a digit");
	draw->setAlignment(mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::TOP);
	draw->setMinSize({ 333, -1 });
	draw->setMinSpaceBetween({ minBuffer, minBuffer });
	draw->setPosition(
		400,
		recognize->getBounds().top + recognize->getBounds().height
			+ minBuffer * 2
	);

	playFlappy = addChild<mk::GUI::Button>(font, "Play Flappy Bird");
	playFlappy->setAlignment(
		mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::TOP
	);
	playFlappy->setMinSize({ 333, -1 });
	playFlappy->setMinSpaceBetween({ minBuffer, minBuffer });
	playFlappy->setPosition(
		400, draw->getBounds().top + draw->getBounds().height + minBuffer * 2
	);
}

void MainMenu::onUpdate(float dt) {
	if (recognize->isPressed())
		mk::Game::get().addScene(std::make_unique<ImageClassifierScene>());
	if (draw->isPressed())
		mk::Game::get().addScene(std::make_unique<DrawBoard>());
	if (playFlappy->isPressed())
		mk::Game::get().addScene(std::make_unique<FlappyLevel>());
}
