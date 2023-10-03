//
// Created by mateusz on 10/2/23.
//

#include "FlappyBars.hpp"

FlappyBars::FlappyBars(float top, float bottom, float positionX) {
	float innerXDiff = (PIPE_END_SIZE.x - PIPE_BODY_SIZE.x) / 2;

	// top bar : end, body
	rects.emplace_back(
		positionX + innerXDiff,
		top - PIPE_BODY_SIZE.y,
		PIPE_BODY_SIZE.x,
		PIPE_BODY_SIZE.y
	);
	rects.emplace_back(
		positionX, top - PIPE_END_SIZE.y, PIPE_END_SIZE.x, PIPE_END_SIZE.y
	);

	// bottom bar : end, body
	rects.emplace_back(
		positionX + innerXDiff, bottom, PIPE_BODY_SIZE.x, PIPE_BODY_SIZE.y
	);
	rects.emplace_back(positionX, bottom, PIPE_END_SIZE.x, PIPE_END_SIZE.y);
}

void FlappyBars::move(float deltaX) {
	for (auto &rect : rects) rect.left += deltaX;
}

const std::vector<mk::RectF> &FlappyBars::getRects() const { return rects; }

mk::Math::Vector2f FlappyBars::getBottomTopLeft() const {
	return rects[3].getPosition();
}

mk::Math::Vector2f FlappyBars::getTopTopLeft() const {
	return { rects[1].left, rects[0].top };
}
