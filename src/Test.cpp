//
// Created by mateusz on 9/16/23.
//

#include "Test.hpp"

#include "ModelLoader/NeuralNetworkManager.hpp"
#include "Scenes/idx/Reader.hpp"

#include <ai/Base/NeuralNetwork.hpp>
#include <ai/Coaches/NeuralNetworkCoach.hpp>
#include <iostream>

void run() {
	std::srand(0);

	ai::NeuralNetwork network({ 1, 2 }, std::make_unique<ai::Sigmoid>());
	network.randomizeWeightsAndBiases(0);

	ai::TrainingSet set;

	for (int i = 0; i < 100; i++) {
		double           a = std::rand() % 100;
		ai::TrainingItem item;
		item.input = { a / 100.0 };
		if (a >= 50)
			item.correctOutput = { 1, 0 };
		else
			item.correctOutput = { 0, 1 };
		set.push_back(item);
	}

	ai::NeuralNetworkCoach coach(network, std::make_unique<ai::DifferenceSquaredCostFunction>());
	coach.train(set, 1, 1, 50);

	ai::NeuralNetworkManager::saveNeuralNetwork(network, "lessThan50.json");
}

void run2() {
	auto network = ai::NeuralNetworkManager::loadNeuralNetwork("lessThan50.json");

	int a = 0;
	while (a != -1) {
		std::cout << "Give me a number: ";
		std::cin >> a;
		std::cout << '\n';
		auto out = network.calculateOutputs({ (double) a / 100 }).activations.back();
		if (out[0] < out[1])
			std::cout << "less than 50" << '\n';
		else
			std::cout << "more than 50" << '\n';
	}
}

static ai::TrainingSet createSetFromReader(idx::Reader &reader, uint maxSize = -1) {
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

void teachImages() {
	idx::Reader reader("resources/train-images.idx3-ubyte", "resources/train-labels.idx1-ubyte");

	ai::NeuralNetwork network({ 784, 100, 10 }, std::make_unique<ai::ReLU>());
	network.randomizeWeightsAndBiases(0);

	ai::NeuralNetworkCoach coach(network, std::make_unique<ai::DifferenceSquaredCostFunction>());

	auto set = createSetFromReader(reader, 60'000);
	std::cerr << "Begin training: \n";
	coach.train(set, 0.1, 128, 20);

	std::string modelPath = "digitRecognition.json";
	ai::NeuralNetworkManager::saveNeuralNetwork(network, modelPath);
	std::cout << "Saved at: " << modelPath << '\n';
}
