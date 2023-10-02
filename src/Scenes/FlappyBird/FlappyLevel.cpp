//
// Created by mateusz on 9/30/23.
//

#include "FlappyLevel.hpp"

#include "FlappyKeyboardController.hpp"
#include "Game/Game.hpp"

FlappyLevel::FlappyLevel() {
	initialViewportSize = mk::Game::get().getViewportSize();
	mk::Math::Vector2u viewportSize(160, 120);
	mk::Game::get().setViewportSize(viewportSize.as<sf::Vector2f>());

	game = std::make_unique<FlappyGame>(std::make_unique<FlappyKeyboardController>(), viewportSize, 20);

	renderer = addChild<FlappyRenderer>(game.get());
}

FlappyLevel::~FlappyLevel() { mk::Game::get().setViewportSize(initialViewportSize); }
