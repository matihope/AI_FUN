//
// Created by mateusz on 10/2/23.
//

#include "FlappyBars.hpp"

FlappyBars::FlappyBars(float top, float bottom, float width, float height, float positionX):
	topBar(positionX, top - height, width, height),
	bottomBar(positionX, bottom, width, height) {}

const mk::RectF &FlappyBars::getTop() const { return topBar; }

const mk::RectF &FlappyBars::getBottom() const { return bottomBar; }

void FlappyBars::move(float deltaX) {
	topBar.left += deltaX;
	bottomBar.left += deltaX;
}
