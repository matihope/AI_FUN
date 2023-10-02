//
// Created by mateusz on 9/20/23.
//

#include "ImageClassifierScene.hpp"

#include "Base/NeuralNetwork.hpp"
#include "GUI/GUI.hpp"
#include "Game/Game.hpp"
#include "IdxDigitTrainer.hpp"
#include "ModelLoader/NeuralNetworkManager.hpp"
#include "Random/Random.hpp"
#include "idx/Reader.hpp"

#include <cstdlib>

ImageClassifierScene::ImageClassifierScene():
	reader("resources/t10k-images.idx3-ubyte", "resources/t10k-labels.idx1-ubyte") {
	mk::Random::initRandom();

	viewer = addChild<IdxImageViewer>(reader);

	float viewSize = 600.f;
	float viewPosX = (800.f - viewSize) / 2.f;
	float viewPosY = 25.f;
	float buffer   = 5.f;
	viewer->setScale(viewSize / 28.f, viewSize / 28.f);
	viewer->setPosition(viewPosX, viewPosY);

	auto font = mk::Game::get().getFont();

	using namespace mk::GUI;

	realLabel = addChild<Label>(font);
	realLabel->setAlignment(HAlignment::LEFT, VAlignment::TOP);
	realLabel->setPosition(viewPosX + buffer, viewPosY + viewSize + buffer);
	realLabel->setTextSize(48);

	aiLabel = addChild<Label>(font);
	aiLabel->setAlignment(HAlignment::RIGHT, VAlignment::TOP);
	aiLabel->setPosition(viewPosX + viewSize - buffer, viewPosY + viewSize + buffer);
	aiLabel->setTextSize(48);

	idLabel = addChild<Label>(font);
	idLabel->setAlignment(HAlignment::MIDDLE, VAlignment::TOP);
	idLabel->setPosition(400.0, viewPosY + viewSize + buffer);
	idLabel->setTextSize(32);

	network = std::make_unique<ai::NeuralNetwork>(
		ai::NeuralNetworkManager::loadNeuralNetwork("models/digits/digitsUltimate.json"));
	testImage(0);

	prevImageBtn = addChild<Button>(font, "Previous image");
	prevImageBtn->setMinSize({ 400 - buffer * 2, -1 });
	prevImageBtn->setMinSpaceBetween({ buffer, buffer });
	prevImageBtn->setPosition(buffer, 800 - buffer);
	prevImageBtn->setAlignment(HAlignment::LEFT, VAlignment::BOTTOM);

	nextImageBtn = addChild<Button>(font, "Next image");
	nextImageBtn->setMinSize({ 400 - 2 * buffer, -1 });
	nextImageBtn->setMinSpaceBetween({ buffer, buffer });
	nextImageBtn->setPosition(800 - buffer, 800 - buffer);
	nextImageBtn->setAlignment(HAlignment::RIGHT, VAlignment::BOTTOM);

	randomImageBtn = addChild<Button>(font, "Random image");
	randomImageBtn->setMinSize({ 400 - 2 * buffer, -1 });
	randomImageBtn->setMinSpaceBetween({ buffer, buffer });
	randomImageBtn->setPosition(800 - buffer, 800 - nextImageBtn->getBounds().height - 3 * buffer);
	randomImageBtn->setAlignment(HAlignment::RIGHT, VAlignment::BOTTOM);

	wrongImageBtn = addChild<Button>(font, "Next wrong image");
	wrongImageBtn->setMinSize({ 400 - 2 * buffer, -1 });
	wrongImageBtn->setMinSpaceBetween({ buffer, buffer });
	wrongImageBtn->setPosition(buffer, 800 - prevImageBtn->getBounds().height - 3 * buffer);
	wrongImageBtn->setAlignment(HAlignment::LEFT, VAlignment::BOTTOM);
}

void ImageClassifierScene::testImage(uint imageId) {
	currImg = imageId;
	currImg = (currImg + reader.getImages().size()) % reader.getImages().size();
	viewer->setImageIndex(imageId);
	auto lbl = reader.getImages()[imageId].label;
	realLabel->setText("Real: " + lbl);

	auto item  = IdxDigitTrainer::createItemFromIdxImage(reader.getImages()[imageId]);
	auto index = network->calculateBestIndex(item.input);

	aiLabel->setText("Ai: " + std::to_string(index));
	aiLabel->setColor((index == (lbl[0] - '0')) ? sf::Color::Green : sf::Color::Red);
	idLabel->setText("Image: " + std::to_string(imageId));
}

void ImageClassifierScene::onPhysicsUpdate(float dt) {
	if (prevImageBtn->isPressed()) prevImage();
	if (nextImageBtn->isPressed()) nextImage();
	if (randomImageBtn->isPressed()) {
		uint newIndex = mk::Random::getInt<uint>(0, reader.getImages().size() - 1);
		testImage(newIndex);
	}
	if (wrongImageBtn->isPressed()) {
		nextImage();
		while (aiLabel->getText().back() == realLabel->getText().back()) nextImage();
	}
}

void ImageClassifierScene::nextImage() { testImage(++currImg); }

void ImageClassifierScene::prevImage() { testImage(--currImg); }
