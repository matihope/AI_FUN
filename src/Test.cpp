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

void run() {}

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
