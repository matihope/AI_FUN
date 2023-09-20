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
	idx::Reader reader("resources/train-images.idx3-ubyte",
	                   "resources/train-labels.idx1-ubyte");
}
