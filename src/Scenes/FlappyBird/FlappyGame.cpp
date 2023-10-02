//
// Created by mateusz on 9/30/23.
//

#include "FlappyGame.hpp"

FlappyGame::FlappyGame(std::unique_ptr<FlappyController> controller, mk::Math::Vector2u gameSize,
                       float playerPositionX):
	controller(std::move(controller)),
	player(controller.get(), { 16, 16 }),                // 16x16 - playerSize
	playerPositionX(playerPositionX) {
	bars.emplace_back(30, 70, 64, 128, gameSize.x / 2);  // 64x128 - barSize
}

mk::Math::Vector2f FlappyGame::getPlayerPosition() const { return { playerPositionX, player.getPosition() }; }

void FlappyGame::gameUpdate(float dt) {
	player.gameUpdate(dt, *this);
	bars.front().move(-25 * dt);
}

float FlappyGame::getPlayerVelocity() const { return player.getVelocity(); }

bool FlappyGame::isPlayerDead() const { return player.isDead(); }

const std::list<FlappyBars> &FlappyGame::getBars() const { return bars; }
