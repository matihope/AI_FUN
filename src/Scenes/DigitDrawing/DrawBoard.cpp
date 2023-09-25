//
// Created by mateusz on 9/25/23.
//

#include "DrawBoard.hpp"

#include "GUI/Button.hpp"
#include "Math/Vector2f.hpp"
#include "ModelLoader/NeuralNetworkManager.hpp"

#include <Game/Game.hpp>

DrawBoard::DrawBoard(uint boardSizePixels): boardSize(boardSizePixels) {
	batch = addChild<mk::SpriteBatch>();
	batch->makeGrid({ boardSize, boardSize }, { 1.0, 1.0 });
	for (auto &sprite : batch->getSprites()) sprite.setColor(sf::Color::White);
	batch->setScale(400.f / boardSize, 400.f / boardSize);
	batch->setPosition(25.f, 25.f);
	boardData.resize(boardSize * boardSize, 0.0);

	aiAnswer = addChild<mk::GUI::Label>(mk::Game::get().getFont());
	aiAnswer->setAlignment(mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::CENTER);
	aiAnswer->setPosition(800.f - (800.f - 400.f - 25.f) / 2.f, 212.5f);
	aiAnswer->setText("Draw a digit");

	resetBoard = addChild<mk::GUI::Button>(mk::Game::get().getFont(), "Reset board");
	resetBoard->setMinSpaceBetween({ 15, 15 });
	resetBoard->setPosition(212.5, 425.f + 5);
	resetBoard->setAlignment(mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::TOP);

	network = std::make_unique<ai::NeuralNetwork>(ai::NeuralNetworkManager::loadNeuralNetwork("newDigits2.json"));
}

void DrawBoard::onPhysicsUpdate(float dt) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto [mX, mY] = mk::Game::get().getMousePos();
		mk::Math::Vector2f mousePos(mX, mY);

		mousePos.x -= batch->getPosition().x;
		mousePos.y -= batch->getPosition().y;

		if (mousePos.x < 400.f && mousePos.y < 400.f) {
			auto intPos = (mousePos / batch->getScale().x).type<uint>();
			uint index  = intPos.y * boardSize + intPos.x;

			batch->getSprite(index).setColor(sf::Color::Black);
			boardData[index] = 1.0;

			aiAnswer->setText("AI guess: " + std::to_string(network->calculateBestIndex(boardData)));
		}
	}

	if (resetBoard->isPressed()) {
		for (auto &sprite : batch->getSprites()) sprite.setColor(sf::Color::White);
		boardData.resize(boardSize * boardSize, 0.0);
	}
}

const std::vector<double> &DrawBoard::getBoardAsData() const { return boardData; }

void DrawBoard::handleEvent(const sf::Event &event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) mk::Game::get().popScene();
}