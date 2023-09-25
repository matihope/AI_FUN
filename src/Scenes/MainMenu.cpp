//
// Created by mateusz on 9/25/23.
//

#include "MainMenu.hpp"

#include "Game/Game.hpp"
#include "Scenes/DigitDrawing/DrawBoard.hpp"
#include "Scenes/MnistTestImgRecognition/ImageClassifierScene.hpp"

MainMenu::MainMenu() {
	auto font = mk::Game::get().getFont();

	float minBuffer = 5;

	recognize = addChild<mk::GUI::Button>(font, "View test images");
	recognize->setAlignment(mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::CENTER);
	recognize->setMinSize({ 333, -1 });
	recognize->setMinSpaceBetween({ minBuffer, minBuffer });
	recognize->setPosition(400, 400);

	draw = addChild<mk::GUI::Button>(font, "Draw a digit");
	draw->setAlignment(mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::CENTER);
	draw->setMinSize({ 333, -1 });
	draw->setMinSpaceBetween({ minBuffer, minBuffer });
	draw->setPosition(400, 400 + recognize->getBounds().height + minBuffer * 2);
}

void MainMenu::onUpdate(float dt) {
	if (recognize->isPressed()) mk::Game::get().addScene(std::make_unique<ImageClassifierScene>());
	if (draw->isPressed()) mk::Game::get().addScene(std::make_unique<DrawBoard>());
}

void MainMenu::handleEvent(const sf::Event &event) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			mk::Game::get().stop();
		default:
			break;
		}
		break;
	default:
		break;
	}
}
