//
// Created by mateusz on 9/16/23.
//

#include "Test.hpp"

#include "Scenes/idx/Reader.hpp"

#include <ai/Base/NeuralNetwork.hpp>
#include <ai/Coaches/NeuralNetworkCoach.hpp>
#include <iostream>

void run() {
	//	ai::NeuralNetwork network({ 2, 3, 2 }, std::make_unique<ai::Sigmoid>());
	//	ai::NeuralNetworkCoach coach(
	//		network, std::make_unique<ai::DifferenceSquaredCostFunction>());
	//	ai::TrainingSet input = {
	//		ai::TrainingItem({ .5, .3 }, { 1, 0 }),
	//		ai::TrainingItem({ .1, .15 }, { 0, 1 }),
	//		ai::TrainingItem({ -.05, .1 }, { 0, 1 }),
	//	};
	//
	//	for (int i = 0; i < 10'000; i++) {
	//		coach.train(input, 0.1);
	//		std::cout << coach.cost(input) << '\n';
	//	}
	//	idx::Reader reader("resources/train-images.idx3-ubyte",
	//	                   "resources/train-labels.idx1-ubyte");

	std::srand(0);


	ai::NeuralNetwork network({ 1, 2 }, std::make_unique<ai::ReLU>());
	network.randomizeWeightsAndBiases(0);

	ai::TrainingSet set;

	for (int i = 0; i < 100; i++) {
		double a = std::rand() % 100;
		if (std::rand() % 2 == 1) a *= -1;
		ai::TrainingItem item;
		item.input = { a };
		if (a >= 0)
			item.correctOutput = { 1, 0 };
		else
			item.correctOutput = { 0, 1 };
		set.push_back(item);
	}

	ai::NeuralNetworkCoach coach(
		network, std::make_unique<ai::DifferenceSquaredCostFunction>());

	for (int i = 0; i < 1'000; i++) {
		coach.train(set, 0.5);
		std::cout << coach.cost(set) << '\n';
	}

	int a = 0;
	while (a != -1) {
		std::cout << "Give me a number: ";
		std::cin >> a;
		std::cout << '\n';
		auto out = network.calculateOutputs({ (double) a }).activations.back();
		if (out[0] < out[1])
			std::cout << "Negative" << '\n';
		else
			std::cout << "Positive" << '\n';
	}

	//	for (int i = 1; i < 3; i++) {
	//		for(auto w: network.getLayer(i).)
	//	}
}
