//
// Created by mateusz on 9/26/23.
//

#include "TestImageTransitions.hpp"

#include "Game/Game.hpp"
#include "Random/Random.hpp"

#include <Math/Math.hpp>

TestImageTransitions::TestImageTransitions():
	reader("resources/t10k-images.idx3-ubyte", "resources/t10k-labels.idx1-ubyte") {
	setScale(mk::Game::get().getViewportSize().x / 28.0, mk::Game::get().getViewportSize().y / 28.0);

	viewer = addChild<IdxImageViewer>(reader);
	viewer->setImageIndex(0);
}

void TestImageTransitions::handleEvent(const sf::Event &event) {
	if (event.type == sf::Event::KeyPressed) {
		double backgroundColor = 0.0;
		auto   img             = reader.getImages()[0];
		int    timesH          = 0;
		int    timesV          = 0;

		switch (event.key.code) {
		case sf::Keyboard::Right:
			timesH++;
			break;
		case sf::Keyboard::Left:
			timesH--;
			break;
		case sf::Keyboard::Up:
			timesV--;
			break;
		case sf::Keyboard::Down:
			timesV++;
			break;
		}
		auto bounds = getBounds(img, backgroundColor);

		if (bounds.left + timesH < 0) timesH = 0;
		if (bounds.left + bounds.width + timesH >= img.pixels.size()) timesH = 0;

		if (bounds.top + timesV < 0) timesV = 0;
		if (bounds.top + bounds.height + timesV >= img.pixels[0].size()) timesV = 0;

		;

		reader.setImage(0, shiftHorizontal(shiftVertical(img, backgroundColor, timesV), backgroundColor, timesH));
		viewer->setImageIndex(0);
	}
}

sf::IntRect TestImageTransitions::getBounds(const idx::Image &image, double backgroundColor) {
	sf::IntRect rect(INT_INFINITY, INT_INFINITY, 0, 0);
	for (int y = 0; y < image.pixels.size(); y++) {
		for (int x = 0; x < image.pixels[y].size(); x++) {
			if (image.pixels[y][x] != backgroundColor) {
				rect.top    = std::min(rect.top, y);
				rect.left   = std::min(rect.left, x);
				rect.width  = std::max(rect.width, x - rect.left);
				rect.height = std::max(rect.height, y - rect.top);
			}
		}
	}
	return rect;
}

idx::Image TestImageTransitions::shiftLeft(idx::Image image, double backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			image.pixels[y][x] = (x != width - 1) ? image.pixels[y][x + 1] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::shiftLeft(idx::Image image, double backgroundColor, int times) {
	while (times--) image = shiftLeft(image, backgroundColor);
	return image;
}

idx::Image TestImageTransitions::shiftRight(idx::Image image, double backgroundColor, int times) {
	while (times--) image = shiftRight(image, backgroundColor);
	return image;
}

idx::Image TestImageTransitions::shiftRight(idx::Image image, double backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = width - 1; x >= 0; x--)
		for (int y = 0; y < height; y++) image.pixels[y][x] = (x != 0) ? image.pixels[y][x - 1] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::shiftHorizontal(idx::Image image, double backgroundColor, int times) {
	if (times > 0) return shiftRight(image, backgroundColor, times);
	return shiftLeft(image, backgroundColor, -times);
}

idx::Image TestImageTransitions::shiftVertical(idx::Image image, double backgroundColor, int times) {
	if (times > 0) return shiftDown(image, backgroundColor, times);
	return shiftUp(image, backgroundColor, -times);
}

idx::Image TestImageTransitions::shiftDown(idx::Image image, double backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = 0; x < width; x++)
		for (int y = height - 1; y >= 0; y--) image.pixels[y][x] = (y != 0) ? image.pixels[y - 1][x] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::shiftUp(idx::Image image, double backgroundColor, int times) {
	while (times--) image = shiftUp(image, backgroundColor);
	return image;
}

idx::Image TestImageTransitions::shiftDown(idx::Image image, double backgroundColor, int times) {
	while (times--) image = shiftDown(image, backgroundColor);
	return image;
}

idx::Image TestImageTransitions::shiftUp(idx::Image image, double backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			image.pixels[y][x] = (y != height - 1) ? image.pixels[y + 1][x] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::randomShift(idx::Image image, double backgroundColor) {
	auto bounds = getBounds(image, backgroundColor);
	int  timesH = mk::Random::getInt(-bounds.left, (int) image.pixels.size() - 1 - bounds.left - bounds.width);
	int  timesV = mk::Random::getInt(-bounds.top, (int) image.pixels[0].size() - 1 - bounds.top - bounds.height);
	return shiftHorizontal(shiftVertical(image, backgroundColor, timesV), backgroundColor, timesH);
}
