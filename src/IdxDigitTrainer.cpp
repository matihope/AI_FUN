//
// Created by mateusz on 9/23/23.
//

#include "IdxDigitTrainer.hpp"

#include "ModelLoader/NeuralNetworkManager.hpp"

#include <iostream>

ai::TrainingItem IdxDigitTrainer::createItemFromIdxImage(const idx::Image &image) {
	std::vector<double> inputs;
	std::vector<double> outputs(10, 0);
	for (const auto &imgRow : image.pixels)
		for (auto pixel : imgRow) inputs.push_back((double) pixel / 255.0);
	outputs[image.label[0] - '0'] = 1.0;
	return { inputs, outputs };
}

ai::TrainingSet IdxDigitTrainer::createSetFromReader(const idx::Reader &reader, uint maxSize) {
	ai::TrainingSet set;
	for (const auto &img : reader.getImages()) {
		set.push_back(createItemFromIdxImage(img));
		if (maxSize != -1 && set.size() >= maxSize) break;
	}
	return set;
}

void IdxDigitTrainer::teachImages() {
	std::cerr << "Begin teaching: \n";

	ai::NeuralNetwork network({ 784, 100, 10 }, std::make_unique<ai::ReLU>());
	network.randomizeWeightsAndBiases(0);

	ai::NeuralNetworkCoach coach(network, std::make_unique<ai::DifferenceSquaredCostFunction>());

	idx::Reader reader("resources/train-images.idx3-ubyte", "resources/train-labels.idx1-ubyte");
	auto        set = createSetFromReader(reader, 60'000);
	std::cerr << "Begin training: \n";
	coach.train(set, 0.1, 128, 20);

	std::string modelPath = "digitRecognition.json";
	ai::NeuralNetworkManager::saveNeuralNetwork(network, modelPath);
	std::cout << "Saved at: " << modelPath << '\n';
}

void IdxDigitTrainer::testImages() {
	std::cerr << "Begin testing: \n";
	auto network = ai::NeuralNetworkManager::loadNeuralNetwork("digitRecognition.json");

	idx::Reader testReader("resources/t10k-images.idx3-ubyte", "resources/t10k-labels.idx1-ubyte");
	auto        testSet = createSetFromReader(testReader);
	uint        good    = 0;
	for (const auto &item : testSet) {
		uint index = network.calculateBestIndex(item.input);
		if (item.correctOutput[index] == 1.0) good++;
	}
	std::cout << "Good: " << good << ", bad: " << testSet.size() - good
			  << ", correct: " << (double) good / testSet.size() * 100 << "%\n";
}

void IdxDigitTrainer::moreTrainer() {
	std::cerr << "Begin teaching more!: \n";

	auto        network = ai::NeuralNetworkManager::loadNeuralNetwork("digitRecognition.json");
	idx::Reader reader("resources/train-images.idx3-ubyte", "resources/train-labels.idx1-ubyte");
	auto        set = createSetFromReader(reader, 60'000);
	std::cerr << "Begin training: \n";

	ai::NeuralNetworkCoach coach(network, std::make_unique<ai::DifferenceSquaredCostFunction>());
	coach.train(set, 0.025, 128, 20);

	ai::NeuralNetworkManager::saveNeuralNetwork(network, "digitRecognitionMore.json");

	idx::Reader testReader("resources/t10k-images.idx3-ubyte", "resources/t10k-labels.idx1-ubyte");
	auto        testSet = createSetFromReader(testReader);
	uint        good    = 0;
	for (const auto &item : testSet) {
		uint index = network.calculateBestIndex(item.input);
		if (item.correctOutput[index] == 1.0) good++;
	}
	std::cout << "Good: " << good << ", bad: " << testSet.size() - good
			  << ", correct: " << (double) good / testSet.size() * 100 << "%\n";
}
