//
// Created by mateusz on 9/30/23.
//

#include "FlappyGame.hpp"

FlappyGame::FlappyGame(
	std::unique_ptr<FlappyController> controller,
	mk::Math::Vector2u                gameSize,
	float                             playerPositionX
):
	  controller(std::move(controller)),
	  player(controller.get(), { 16, 16 }),           // 16x16 - playerSize
	  playerPositionX(playerPositionX) {
	bars.emplace_back(30.f, 70.f, gameSize.x / 2.f);  // 64x128 - barSize
}

mk::Math::Vector2f FlappyGame::getPlayerPosition() const {
	return { playerPositionX, player.getPosition() };
}

void FlappyGame::gameUpdate(float dt) {
	player.gameUpdate(dt, *this);

	for (const auto &bar : bars) {
		auto playerRect = getPlayerRect();
		for (const auto &rect : bar.getRects())
			if (playerRect.overlaps(rect)) player.die();
	}

	if (!player.isDead()) bars.front().move(-BAR_MOVE_SPEED * dt);
}

float FlappyGame::getPlayerVelocity() const { return player.getVelocity(); }

bool FlappyGame::isPlayerDead() const { return player.isDead(); }

const std::list<FlappyBars> &FlappyGame::getBars() const { return bars; }

float FlappyGame::getBarMoveSpeed() const { return BAR_MOVE_SPEED; }

mk::RectF FlappyGame::getPlayerRect() const {
	return { playerPositionX,
		     player.getPosition(),
		     (float) player.getPlayerSize().x,
		     (float) player.getPlayerSize().y };
}
