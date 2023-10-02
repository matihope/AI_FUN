//
// Created by mateusz on 10/1/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYKEYBOARDCONTROLLER_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYKEYBOARDCONTROLLER_HPP_

#include "FlappyController.hpp"

class FlappyKeyboardController: public FlappyController {
public:
	FlappyKeyboardController() = default;
	bool shouldJump(FlappyGame &game) override;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYKEYBOARDCONTROLLER_HPP_
