//
// Created by mateusz on 10/1/23.
//

#include "FlappyKeyboardController.hpp"

#include "FlappyGame.hpp"

#include <SFML/Graphics.hpp>

bool FlappyKeyboardController::shouldJump(FlappyGame &game) {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}
