//
// Created by mateusz on 9/30/23.
//

#include "FlappyPlayer.hpp"

#include "FlappyGame.hpp"

FlappyPlayer::FlappyPlayer(FlappyController *controller): controller(controller) {}

void FlappyPlayer::physicsUpdate(float dt, FlappyGame &game) {
	if (controller->shouldJump(game)) {}
}

float FlappyPlayer::getPosition() const { return position; }
