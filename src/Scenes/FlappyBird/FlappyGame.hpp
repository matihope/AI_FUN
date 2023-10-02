//
// Created by mateusz on 9/30/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYGAME_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYGAME_HPP_

#include "FlappyController.hpp"
#include "FlappyPlayer.hpp"
#include "Math/Vector2f.hpp"

#include <memory>

class FlappyGame {
public:
	explicit FlappyGame(std::unique_ptr<FlappyController> controller, mk::Math::Vector2u gameSize,
	                    float playerPositionX);

	[[nodiscard]] mk::Math::Vector2f getPlayerPosition() const;

private:
	FlappyPlayer                      player;
	float                             playerPositionX;
	std::unique_ptr<FlappyController> controller;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYGAME_HPP_
