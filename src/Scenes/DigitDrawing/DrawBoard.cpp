//
// Created by mateusz on 9/25/23.
//

#include "DrawBoard.hpp"

#include "GUI/Button.hpp"
#include "Math/Math.hpp"
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
	aiAnswer->setAlignment(
		mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::CENTER
	);
	aiAnswer->setPosition(800.f - (800.f - 400.f - 25.f) / 2.f, 212.5f);
	aiAnswer->setText("Draw a digit");

	aiOther = addChild<mk::GUI::Label>(mk::Game::get().getFont());
	aiOther->setAlignment(
		mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::TOP
	);
	auto aiAnswerBounds = aiAnswer->getBounds();
	aiOther->setPosition(
		800.f - (800.f - 400.f - 25.f) / 2.f,
		aiAnswerBounds.top + aiAnswerBounds.height + 15
	);
	aiOther->setColor(sf::Color(120, 120, 120));

	resetBoard
		= addChild<mk::GUI::Button>(mk::Game::get().getFont(), "Reset board");
	resetBoard->setMinSpaceBetween({ 15, 15 });
	resetBoard->setPosition(212.5, 425.f + 5);
	resetBoard->setAlignment(
		mk::GUI::HAlignment::MIDDLE, mk::GUI::VAlignment::TOP
	);

	network = std::make_unique<ai::NeuralNetwork>(
		ai::NeuralNetworkManager::loadNeuralNetwork(
			"models/digits/digitsUltimateSoftMax.json"
		)
	);
}

void DrawBoard::onUpdate(float dt) {
	if (mk::Game::get().isWindowActive()
	    && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto [mX, mY] = mk::Game::get().getMousePos();
		mk::Math::Vector2f mousePos(mX, mY);

		mousePos.x -= batch->getPosition().x;
		mousePos.y -= batch->getPosition().y;

		if (0 <= mousePos.x && mousePos.x < 400.f && 0 <= mousePos.y
		    && mousePos.y < 400.f) {
			auto intPos = (mousePos / batch->getScale().x).type<int>();

			if (!hasDrawnLastUpdate) lastMousePos = intPos;

			for (auto pos : mk::Math::drawLine(lastMousePos, intPos)) {
				int index = pos.y * (int) boardSize + pos.x;

				std::vector indices = { index,
					                    index - (int) boardSize,
					                    index + (int) boardSize };
				if (index / boardSize == (index + 1) / boardSize)
					indices.push_back(index + 1);
				if (index / boardSize == (index - 1) / boardSize)
					indices.push_back(index - 1);

				for (auto i : indices) {
					if (0 <= i && i < batch->getSize()) {
						batch->getSprite(i).setColor(sf::Color::Black);
						boardData[i] = 1.0;
					}
				}
			}

			lastMousePos       = intPos;
			hasDrawnLastUpdate = true;

			auto outs = network->calculate(boardData);

			std::vector<std::pair<double, uint>> sorted;
			for (uint i = 0; i < outs.size(); i++)
				sorted.emplace_back(outs[i], i);
			std::sort(
				sorted.begin(),
				sorted.end(),
				[&](const auto a, const auto b) { return a.first > b.first; }
			);

			aiAnswer->setText(
				"AI guess: " + std::to_string(sorted.front().second)
			);

			std::string other;
			for (auto &vert : sorted)
				other += std::to_string(vert.second) + ": "
				       + std::to_string(vert.first * 100) + "%\n";
			aiOther->setText(other);

		} else {
			hasDrawnLastUpdate = false;
		}
	} else {
		hasDrawnLastUpdate = false;
	}

	if (resetBoard->isPressed()) {
		for (auto &sprite : batch->getSprites())
			sprite.setColor(sf::Color::White);
		boardData.clear();
		boardData.resize(boardSize * boardSize, 0.0);
		aiAnswer->setText("Empty board");
		aiOther->setText("");
	}
}

const std::vector<double> &DrawBoard::getBoardAsData() const {
	return boardData;
}
