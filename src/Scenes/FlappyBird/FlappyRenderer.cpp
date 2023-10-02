//
// Created by mateusz on 10/1/23.
//

#include "FlappyRenderer.hpp"

#include "FlappyKeyboardController.hpp"
#include "Game/Game.hpp"
#include "Nodes/RectShape.hpp"
#include "ResourceManager/ResourceManager.hpp"

FlappyRenderer::FlappyRenderer(FlappyGame *game, mk::Math::Vector2f gameSize): game(game), gameSize(gameSize) {
	playerTexture     = &mk::ResourceManager::get().getTexture("resources/flappy_bird/flappy_sheet.png");
	backgroundTexture = &mk::ResourceManager::get().getTexture("resources/flappy_bird/background.png");
	barTexture        = &mk::ResourceManager::get().getTexture("resources/flappy_bird/bars.png");

	playerSprite.setTexture(*playerTexture);

	background1.setTexture(*backgroundTexture);
	background2.setTexture(*backgroundTexture);
	background2.move(backgroundTexture->getSize().x, 0);
	playerRect = sf::IntRect(0, 0, (int) playerTexture->getSize().x / 3, (int) playerTexture->getSize().y);
}

void FlappyRenderer::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(background1, states);
	target.draw(background2, states);

	sf::Sprite top, bottom;
	auto       halfWidth = (int) barTexture->getSize().x / 2;
	top.setTexture(*barTexture);
	top.setTextureRect({ 0, 0, halfWidth, (int) barTexture->getSize().y });
	bottom.setTexture(*barTexture);
	bottom.setTextureRect({ halfWidth, 0, halfWidth, (int) barTexture->getSize().y });

	for (const auto &bar : game->getBars()) {
		top.setPosition(bar.getTop().getPosition().as<sf::Vector2f>());
		bottom.setPosition(bar.getBottom().getPosition().as<sf::Vector2f>());
		target.draw(top, states);
		target.draw(bottom, states);
	}

	target.draw(playerSprite, states);
}

void FlappyRenderer::gameUpdate(float dt) {
	playerSprite.setPosition((game->getPlayerPosition()).as<sf::Vector2f>());

	playerRect.left = 0;
	if (game->getPlayerVelocity() > 0) playerRect.left = playerRect.width;
	if (game->isPlayerDead()) playerRect.left = 2 * playerRect.width;
	playerSprite.setTextureRect(playerRect);

	float backgroundMoveSpeed = 15;
	background1.move(-backgroundMoveSpeed * dt, 0);
	if (background1.getPosition().x < -(float) backgroundTexture->getSize().x)
		background1.move(backgroundTexture->getSize().x * 2, 0);
	background2.move(-backgroundMoveSpeed * dt, 0);
	if (background2.getPosition().x < -(float) backgroundTexture->getSize().x)
		background2.move(backgroundTexture->getSize().x * 2, 0);
}
