//
// Created by mateusz on 9/26/23.
//

#include "TestImageTransitions.hpp"

#include "Game/Game.hpp"
#include "Random/Random.hpp"

#include <Math/Math.hpp>

sf::IntRect TestImageTransitions::getBounds(
	const idx::Image &image, int backgroundColor
) {
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

idx::Image
	TestImageTransitions::shiftLeft(idx::Image image, int backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			image.pixels[y][x]
				= (x != width - 1) ? image.pixels[y][x + 1] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::shiftLeft(
	idx::Image image, int backgroundColor, int times
) {
	while (times--) image = shiftLeft(image, backgroundColor);
	return image;
}

idx::Image TestImageTransitions::shiftRight(
	idx::Image image, int backgroundColor, int times
) {
	while (times--) image = shiftRight(image, backgroundColor);
	return image;
}

idx::Image
	TestImageTransitions::shiftRight(idx::Image image, int backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = width - 1; x >= 0; x--)
		for (int y = 0; y < height; y++)
			image.pixels[y][x]
				= (x != 0) ? image.pixels[y][x - 1] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::shiftHorizontal(
	idx::Image image, int backgroundColor, int times
) {
	if (times > 0) return shiftRight(image, backgroundColor, times);
	return shiftLeft(image, backgroundColor, -times);
}

idx::Image TestImageTransitions::shiftVertical(
	idx::Image image, int backgroundColor, int times
) {
	if (times > 0) return shiftDown(image, backgroundColor, times);
	return shiftUp(image, backgroundColor, -times);
}

idx::Image
	TestImageTransitions::shiftDown(idx::Image image, int backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = 0; x < width; x++)
		for (int y = height - 1; y >= 0; y--)
			image.pixels[y][x]
				= (y != 0) ? image.pixels[y - 1][x] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::shiftUp(
	idx::Image image, int backgroundColor, int times
) {
	while (times--) image = shiftUp(image, backgroundColor);
	return image;
}

idx::Image TestImageTransitions::shiftDown(
	idx::Image image, int backgroundColor, int times
) {
	while (times--) image = shiftDown(image, backgroundColor);
	return image;
}

idx::Image
	TestImageTransitions::shiftUp(idx::Image image, int backgroundColor) {
	int width  = image.pixels[0].size();
	int height = image.pixels.size();

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			image.pixels[y][x]
				= (y != height - 1) ? image.pixels[y + 1][x] : backgroundColor;

	return image;
}

idx::Image TestImageTransitions::randomShift(
	idx::Image image, int backgroundColor, int drawColor
) {
	auto bounds = getBounds(image, backgroundColor);

	image = addRotationAndScale(image, backgroundColor, drawColor);

	int timesH = mk::Random::getInt(
		-bounds.left, (int) image.pixels.size() - 1 - bounds.left - bounds.width
	);
	int timesV = mk::Random::getInt(
		-bounds.top,
		(int) image.pixels[0].size() - 1 - bounds.top - bounds.height
	);
	image = shiftHorizontal(
		shiftVertical(image, backgroundColor, timesV), backgroundColor, timesH
	);
	image = addNoise(image, backgroundColor, drawColor, 4);

	return image;
}

idx::Image TestImageTransitions::addNoise(
	idx::Image image, int backgroundColor, int drawColor, int percentChance
) {
	for (auto &pixel : image.pixels) {
		for (byte &b : pixel) {
			int value = mk::Random::getInt(
				backgroundColor, mk::Random::getInt(0, 128)
			);
			if (mk::Random::getInt(1, 100) <= percentChance) b += (byte) value;
		}
	}
	return image;
}

idx::Image TestImageTransitions::addRotationAndScale(
	idx::Image image, int backgroundColor, int drawColor
) {
	idx::Image image2   = image;
	float      rotation = mk::Random::getReal(-M_PIf / 6, M_PIf / 6);
	float      scale    = mk::Random::getReal(0.6f, 1.4f);

	int center = (image.pixels.size() - 1) / 2;


	for (int y = 0; y < image.pixels.size(); y++) {
		for (int x = 0; x < image.pixels[y].size(); x++) {
			auto sourcePosFloat = mk::Math::rotateVector(
				mk::Math::Vector2f(x - center, y - center), rotation
			);
			sourcePosFloat *= scale;
			sourcePosFloat += center;

			auto [source_x, source_y] = sourcePosFloat.type<int>();
			if (0 <= source_x && source_x < image.pixels.size() && 0 <= source_y
			    && source_y < image.pixels.size())
				image2.pixels[y][x] = image.pixels[source_y][source_x];
			else
				image2.pixels[y][x] = backgroundColor;
		}
	}

	return image2;
}
