//
// Created by mateusz on 9/16/23.
//

#include "Test.hpp"

#include "Scenes/idx/Reader.hpp"

#include <ai/Base/NeuralNetwork.hpp>
#include <ai/Coaches/NeuralNetworkCoach.hpp>
#include <iostream>

void run() {
	//	std::srand(0);
	//
	//
	//	ai::NeuralNetwork network({ 1, 2 }, std::make_unique<ai::ReLU>());
	//	network.randomizeWeightsAndBiases(0);
	//
	//	ai::TrainingSet set;
	//
	//	for (int i = 0; i < 100; i++) {
	//		double a = std::rand() % 100;
	//		//		if (std::rand() % 2 == 1) a *= -1;
	//		ai::TrainingItem item;
	//		item.input = { a / 100.0 };
	//		if (a >= 50)
	//			item.correctOutput = { 1, 0 };
	//		else
	//			item.correctOutput = { 0, 1 };
	//		set.push_back(item);
	//	}
	//
	//	ai::NeuralNetworkCoach coach(network, std::make_unique<ai::DifferenceSquaredCostFunction>());
	//	double                 cost = coach.train(set, 0.1, 16, 1'000);
	//
	//
	//	int a = 0;
	//	while (a != -1) {
	//		std::cout << "Give me a number: ";
	//		std::cin >> a;
	//		std::cout << '\n';
	//		auto out = network.calculateOutputs({ (double) a / 100 }).activations.back();
	//		if (out[0] < out[1])
	//			std::cout << "less than 50" << '\n';
	//		else
	//			std::cout << "more than 50" << '\n';
	//	}

	//	for (int i = 1; i < 3; i++) {
	//		for(auto w: network.getLayer(i).)
	//	}
}
