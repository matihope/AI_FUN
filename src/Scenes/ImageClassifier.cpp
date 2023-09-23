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

ImageClassifier::ImageClassifier(): reader("resources/train-images.idx3-ubyte", "resources/train-labels.idx1-ubyte") {
	viewer = addChild<idxImageViewer>(reader);
	viewer->setScale(400.f / 28.f, 400.f / 28.f);
	viewer->setPosition(200.f, 25.f);

	realLabel = addChild<GUI::Label>(Game::get().getFont());
	realLabel->setAlignment(GUI::HAlignment::LEFT, GUI::VAlignment::BOTTOM);
	realLabel->setPosition(0, 800);
	aiLabel = addChild<GUI::Label>(Game::get().getFont());
	aiLabel->setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::BOTTOM);
	aiLabel->setPosition(800, 800);


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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) testImage(++currImg);
}
