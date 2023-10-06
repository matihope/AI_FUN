//
// Created by mateusz on 10/2/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYBARS_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYBARS_HPP_

#include "Utils/Rect.hpp"

#include <list>
#include <vector>

class FlappyBars {
public:
	static constexpr mk::Math::Vector2f PIPE_END_SIZE  = { 32.f, 9.f };
	static constexpr mk::Math::Vector2f PIPE_BODY_SIZE = { 26.f, 128.f };

	FlappyBars(float top, float bottom, float positionX);

	void move(float deltaX);

	[[nodiscard]] mk::Math::Vector2f getBottomTopLeft() const;
	[[nodiscard]] mk::Math::Vector2f getTopTopLeft() const;

	[[nodiscard]] const std::vector<mk::RectF> &getRects() const;

private:
	std::vector<mk::RectF> rects;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYBARS_HPP_
