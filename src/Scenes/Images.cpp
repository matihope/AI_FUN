//
// Created by mateusz on 9/20/23.
//

#include "Images.hpp"

#include "Base/NeuralNetwork.hpp"
#include "Coaches/NeuralNetworkCoach.hpp"
#include "ModelLoader/NeuralNetworkManager.hpp"

#include <iostream>

ai::TrainingSet createSetFromReader(idx::Reader &reader, uint maxSize = -1) {
	ai::TrainingSet set;
	for (const auto &img : reader.getImages()) {
		std::vector<double> inputs;
		std::vector<double> outputs(10, 0);
		for (const auto &imgRow : img.pixels)
			for (auto pixel : imgRow) inputs.push_back((double) pixel / 255.0);
		outputs[img.label[0] - '0'] = 1.0;
		set.emplace_back(inputs, outputs);
		if (maxSize != -1 && set.size() >= maxSize) break;
	}
	return set;
}

Images::Images(): reader("resources/train-images.idx3-ubyte", "resources/train-labels.idx1-ubyte") {
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			auto image = addChild<MNISTImageViewer>(reader);
			image->setImageIndex(y * 20 + x);
			image->setPosition(x * 29, y * 29);
		}
	}

	std::cerr << "Begin testing: \n";
	auto network = ai::NeuralNetworkManager::loadNeuralNetwork("digitRecognition.json");

	idx::Reader testReader("resources/t10k-images.idx3-ubyte", "resources/t10k-labels.idx1-ubyte");
	uint        good    = 0;
	uint        bad     = 0;
	auto        testSet = createSetFromReader(testReader);
	for (const auto &item : testSet) {
		auto output = network.calculateOutputs(item.input).activations.back();

		double maxVal = 0.0;
		uint   index  = 0.0;
		for (uint i = 0; i < output.size(); i++) {
			if (output[i] > maxVal) {
				index  = i;
				maxVal = output[i];
			}
		}

		if (item.correctOutput[index] == 1.0)
			good++;
		else
			bad++;
	}
	std::cout << "Good: " << good << ", bad: " << bad << ", correct: " << (double) good / testSet.size() * 100 << "%\n";
}
