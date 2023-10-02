//
// Created by mateusz on 9/30/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYPLAYER_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYPLAYER_HPP_

#include "FlappyController.hpp"
#include "Math/Vector2.hpp"

class FlappyGame;

class FlappyPlayer {
public:
	FlappyPlayer(FlappyController *controller, mk::Math::Vector2u playerSize);

	void gameUpdate(float dt, FlappyGame &game);

	[[nodiscard]] float              getPosition() const;
	[[nodiscard]] mk::Math::Vector2u getPlayerSize() const;
	[[nodiscard]] float              getVelocity() const;
	[[nodiscard]] bool               isDead() const;

private:
	const float MAX_VELOCITY      = 3;
	const float GRAVITY           = 0.08;
	const float JUMP_VELOCITY     = -1.5;
	const float DIE_BOTTOM_HEIGHT = 100;

	bool               m_isDead = false;
	float              position{};
	float              velocity{};
	mk::Math::Vector2u playerSize;

	FlappyController *controller;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYPLAYER_HPP_
