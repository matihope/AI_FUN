//
// Created by mateusz on 9/30/23.
//

#include "FlappyPlayer.hpp"

#include "FlappyGame.hpp"

FlappyPlayer::FlappyPlayer(FlappyController *controller, mk::Math::Vector2u playerSize):
	controller(controller),
	playerSize(playerSize) {}

void FlappyPlayer::gameUpdate(float dt, FlappyGame &game) {
	if (m_isDead) return;

	if (controller->shouldJump(game))
		velocity = JUMP_VELOCITY;
	else
		velocity = std::min(MAX_VELOCITY, velocity + GRAVITY);
	position += velocity;

	if (position + playerSize.y >= DIE_BOTTOM_HEIGHT) {
		m_isDead = true;
		position = DIE_BOTTOM_HEIGHT - playerSize.y;
	}
}

float FlappyPlayer::getPosition() const { return position; }

mk::Math::Vector2u FlappyPlayer::getPlayerSize() const { return playerSize; }

float FlappyPlayer::getVelocity() const { return velocity; }

bool FlappyPlayer::isDead() const { return m_isDead; }
