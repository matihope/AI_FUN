//
// Created by mateusz on 9/23/23.
//

#include "IdxDigitTrainer.hpp"

#include "ModelLoader/NeuralNetworkManager.hpp"
#include "Scenes/IdxTestImgRecognition/TestImageTransitions.hpp"

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

void IdxDigitTrainer::teachImages(const std::string &modelPath) {
	ai::NeuralNetwork network({ 784, 100, 10 }, std::make_unique<ai::ReLU>());
	network.randomizeWeightsAndBiases(0);

	ai::NeuralNetworkCoach coach(network, std::make_unique<ai::DifferenceSquaredCostFunction>());

	idx::Reader reader("resources/train-images.idx3-ubyte", "resources/train-labels.idx1-ubyte");
	auto        set = createSetFromReader(reader, 60'000);
	std::cerr << "Begin training: \n";
	coach.train(set, 0.09, 128, 25);

	ai::NeuralNetworkManager::saveNeuralNetwork(network, modelPath);
	std::cout << "Saved at: " << modelPath << '\n';
}

void IdxDigitTrainer::testImages(const std::string &modelPath) {
	auto network = ai::NeuralNetworkManager::loadNeuralNetwork(modelPath);
	testImages(network);
}

void IdxDigitTrainer::teachImagesAugmented(const std::string &modelPath) {
	ai::NeuralNetwork network({ 784, 200, 10 }, std::make_unique<ai::ReLU>());
	teachImagesAugmented(network, modelPath);
}

void IdxDigitTrainer::teachImagesAugmented(ai::NeuralNetwork &network, const std::string &modelPath) {
	network.randomizeWeightsAndBiases(0);

	ai::NeuralNetworkCoach coach(network, std::make_unique<ai::DifferenceSquaredCostFunction>());

	idx::Reader originalReader("resources/train-images.idx3-ubyte", "resources/train-labels.idx1-ubyte");
	idx::Reader reader2 = originalReader;

	std::cerr << "Begin training: \n";
	auto start = std::chrono::high_resolution_clock::now();

	uint images = reader2.getImages().size();
	for (int i = 0; i < 30; i++) {
		for (uint imageIndex = 0; imageIndex < images; imageIndex++)
			reader2.setImage(imageIndex,
			                 TestImageTransitions::randomShift(originalReader.getImages()[imageIndex], 0, 255));
		std::cerr << "Round: " << i << ":\n";
		coach.train(createSetFromReader(reader2, images), 0.09, 128, 3);
	}

	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Training time: " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << "s\n";


	ai::NeuralNetworkManager::saveNeuralNetwork(network, modelPath);
	std::cout << "Saved at: " << modelPath << '\n';
}

void IdxDigitTrainer::testImages(const ai::NeuralNetwork &network) {
	std::cerr << "Begin testing: \n";
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
