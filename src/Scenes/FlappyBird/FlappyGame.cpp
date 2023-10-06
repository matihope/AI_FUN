//
// Created by mateusz on 9/30/23.
//

#include "FlappyGame.hpp"

#include "Random/Random.hpp"

FlappyGame::FlappyGame(
	std::unique_ptr<FlappyController> controller,
	mk::Math::Vector2u                gameSize,
	float                             playerPositionX
):
	  gameSize(gameSize),
	  controller(std::move(controller)),
	  player(controller.get(), { 12, 16 }),  // 16x16 - playerSize
	  playerPositionX(playerPositionX) {
	for (int i = 0; i < 5; i++) generateBar();
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

	if (!player.isDead()) {
		auto barIt = bars.begin();
		while (barIt != bars.end()) {
			barIt->move(-BAR_MOVE_SPEED * dt);
			float positionX
				= barIt->getTopTopLeft().x + FlappyBars::PIPE_END_SIZE.x;

			if (positionX < 0) {
				barIt = bars.erase(barIt);
				generateBar();
			} else {
				barIt++;
			}
		}
	}
}

float FlappyGame::getPlayerVelocity() const { return player.getVelocity(); }

bool FlappyGame::isPlayerDead() const { return player.isDead(); }

const std::list<FlappyBars> &FlappyGame::getBars() const { return bars; }

float FlappyGame::getBarMoveSpeed() { return BAR_MOVE_SPEED; }

mk::RectF FlappyGame::getPlayerRect() const {
	return { playerPositionX,
		     player.getPosition(),
		     (float) player.getPlayerSize().x,
		     (float) player.getPlayerSize().y };
}

void FlappyGame::generateBar() {
	float minPosX = gameSize.x;
	if (!bars.empty()) {
		float lastPos = bars.back().getTopTopLeft().x;

		minPosX
			= std::max(minPosX, lastPos + 2.7f * FlappyBars::PIPE_END_SIZE.x);
	}
	float barDiff = 40.f;
	float height  = mk::Random::getReal(30.f, 125.f);
	bars.emplace_back(
		height - barDiff / 2,
		height + barDiff / 2,
		minPosX
			+ mk::Random::getReal(
				-FlappyBars::PIPE_END_SIZE.x / 4,
				FlappyBars::PIPE_END_SIZE.x / 4
			)
	);  // 64x128 - barSize
}
