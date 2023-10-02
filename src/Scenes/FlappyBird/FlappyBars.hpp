//
// Created by mateusz on 10/2/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYBARS_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYBARS_HPP_

#include "Utils/Rect.hpp"

class FlappyBars {
public:
	FlappyBars(float top, float bottom, float width, float height, float positionX);

	void move(float deltaX);

	[[nodiscard]] const mk::RectF &getTop() const;
	[[nodiscard]] const mk::RectF &getBottom() const;

private:
	mk::RectF topBar, bottomBar;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYBARS_HPP_
