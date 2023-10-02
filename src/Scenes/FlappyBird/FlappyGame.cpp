//
// Created by mateusz on 9/30/23.
//

#include "FlappyGame.hpp"

FlappyGame::FlappyGame(std::unique_ptr<FlappyController> controller, mk::Math::Vector2u gameSize,
                       float playerPositionX):
	controller(std::move(controller)),
	player(controller.get()),
	playerPositionX(playerPositionX) {}

mk::Math::Vector2f FlappyGame::getPlayerPosition() const { return { playerPositionX, player.getPosition() }; }
