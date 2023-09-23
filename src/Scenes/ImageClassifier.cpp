//
// Created by mateusz on 9/20/23.
//

#include "ImageClassifier.hpp"

#include "../Test.hpp"
#include "Base/NeuralNetwork.hpp"
#include "Coaches/NeuralNetworkCoach.hpp"
#include "ModelLoader/NeuralNetworkManager.hpp"
#include "idx/Reader.hpp"

#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

ImageClassifier::ImageClassifier(): reader("resources/t10k-images.idx3-ubyte", "resources/t10k-labels.idx1-ubyte") {
	viewer = addChild<idxImageViewer>(reader);

	float viewSize = 600.f;
	float viewPosX = (800.f - viewSize) / 2.f;
	float viewPosY = 25.f;
	float buffer   = 5.f;
	viewer->setScale(viewSize / 28.f, viewSize / 28.f);
	viewer->setPosition(viewPosX, viewPosY);

	realLabel = addChild<GUI::Label>(Game::get().getFont());
	realLabel->setAlignment(GUI::HAlignment::LEFT, GUI::VAlignment::TOP);
	realLabel->setPosition(viewPosX + buffer, viewPosY + viewSize + buffer);
	realLabel->setTextSize(48);
	aiLabel = addChild<GUI::Label>(Game::get().getFont());
	aiLabel->setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::TOP);
	aiLabel->setPosition(viewPosX + viewSize - buffer, viewPosY + viewSize + buffer);
	aiLabel->setTextSize(48);

	network = std::make_unique<ai::NeuralNetwork>(ai::NeuralNetworkManager::loadNeuralNetwork("digitRecognition.json"));

	testImage(0);
}

void ImageClassifier::testImage(uint imageId) {
	currImg = imageId;
	viewer->setImageIndex(imageId);
	auto lbl = reader.getImages()[imageId].label;
	realLabel->setText("Real: " + lbl);

	auto item   = createItemFromIdxImage(reader.getImages()[imageId]).input;
	auto output = network->calculateOutputs(item).activations.back();

	double maxVal = 0.0;
	uint   index  = 0;
	for (uint i = 0; i < output.size(); i++) {
		if (output[i] > maxVal) {
			index  = i;
			maxVal = output[i];
		}
	}

	aiLabel->setText("Ai: " + std::to_string(index));
}

void ImageClassifier::onPhysicsUpdate(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!pressed) testImage(++currImg);
		pressed = true;
	} else {
		pressed = false;
	}
}
