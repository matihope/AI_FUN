//
// Created by mateusz on 9/19/23.
//

#include "idxImageViewer.hpp"

idxImageViewer::idxImageViewer(idx::Reader &data): data(data) { setImageIndex(0); }

void idxImageViewer::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(digitImage, states);
}

void idxImageViewer::setImageIndex(uint newImageId) {
	imageId = newImageId;

	sf::Image image;
	auto      pixels = data.getImages()[imageId].pixels;
	image.create(pixels[0].size(), pixels.size());

	for (uint y = 0; y < pixels.size(); y++) {
		for (uint x = 0; x < pixels[y].size(); x++) {
			sf::Color color(255 - pixels[y][x], 255 - pixels[y][x], 255 - pixels[y][x]);
			image.setPixel(x, y, color);
		}
	}

	texture.loadFromImage(image);
	digitImage.setTexture(texture);
}
