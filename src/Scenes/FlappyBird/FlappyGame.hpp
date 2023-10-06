//
// Created by mateusz on 9/30/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYGAME_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYGAME_HPP_

#include "FlappyBars.hpp"
#include "FlappyController.hpp"
#include "FlappyPlayer.hpp"
#include "Math/Vector2.hpp"

#include <list>
#include <memory>

class FlappyGame {
public:
	explicit FlappyGame(
		std::unique_ptr<FlappyController> controller,
		mk::Math::Vector2u                gameSize,
		float                             playerPositionX
	);

	void gameUpdate(float dt);

	[[nodiscard]] float              getPlayerVelocity() const;
	[[nodiscard]] mk::Math::Vector2f getPlayerPosition() const;

	[[nodiscard]] bool isPlayerDead() const;

	[[nodiscard]] const std::list<FlappyBars> &getBars() const;

	static float getBarMoveSpeed();

	[[nodiscard]] mk::RectF getPlayerRect() const;

private:
	constexpr static float BAR_MOVE_SPEED = 30;

	mk::Math::Vector2u                gameSize;
	FlappyPlayer                      player;
	float                             playerPositionX;
	std::unique_ptr<FlappyController> controller;

	std::list<FlappyBars> bars;

	void generateBar();
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYGAME_HPP_
