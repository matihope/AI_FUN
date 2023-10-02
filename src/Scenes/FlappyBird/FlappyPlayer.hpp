//
// Created by mateusz on 9/30/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYPLAYER_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYPLAYER_HPP_

#include "FlappyController.hpp"

class FlappyGame;

class FlappyPlayer {
public:
	explicit FlappyPlayer(FlappyController *controller);

	void physicsUpdate(float dt, FlappyGame &game);

	float getPosition() const;

private:
	float position{};
	float velocity{};

	FlappyController *controller;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYPLAYER_HPP_
