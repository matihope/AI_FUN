//
// Created by mateusz on 9/16/23.
//

#include "Test.hpp"

#include "ModelLoader/NeuralNetworkManager.hpp"
#include "idx/Reader.hpp"

#include <Random/Random.hpp>
#include <ai/Base/NeuralNetwork.hpp>
#include <ai/Coaches/NeuralNetworkCoach.hpp>
#include <iostream>

void run() {
	std::srand(0);

	ai::NeuralNetwork network({ 1, 2 }, std::make_unique<ai::Sigmoid>());
	network.randomizeWeightsAndBiases(0);

	ai::TrainingSet set;

	for (int i = 0; i < 100; i++) {
		double           a = mk::Random::getInt(0, 99);
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
		auto out = network.getCalculations({ (double) a / 100 }).activations.back();
		if (out[0] < out[1])
			std::cout << "less than 50" << '\n';
		else
			std::cout << "more than 50" << '\n';
	}
}
