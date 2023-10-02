//
// Created by mateusz on 10/1/23.
//

#include "FlappyRenderer.hpp"

#include "FlappyKeyboardController.hpp"
#include "Game/Game.hpp"

FlappyRenderer::FlappyRenderer(FlappyGame *game): game(game) {
	playerTexture.loadFromFile("resources/flappy_bird/flappy_sheet.png");
	playerSprite.setTexture(playerTexture);
}

void FlappyRenderer::onPhysicsUpdate(float dt) {
	playerSprite.setPosition((game->getPlayerPosition()).as<sf::Vector2f>());
	playerSprite.setTextureRect({ 0, 0, (int) playerTexture.getSize().x / 3, (int) playerTexture.getSize().y });
}

void FlappyRenderer::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(playerSprite, states);
}
