//
// Created by mateusz on 9/30/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYCONTROLLER_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYCONTROLLER_HPP_

class FlappyGame;

class FlappyController {
public:
	virtual ~FlappyController()               = default;
	virtual bool shouldJump(FlappyGame &game) = 0;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYCONTROLLER_HPP_
