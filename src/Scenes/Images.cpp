//
// Created by mateusz on 9/20/23.
//

#include "Images.hpp"

#include "Base/NeuralNetwork.hpp"
#include "Coaches/NeuralNetworkCoach.hpp"

#include <iostream>

Images::Images():
	reader("resources/t10k-images.idx3-ubyte",
           "resources/t10k-labels.idx1-ubyte") {
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			auto image = addChild<MNISTImageViewer>(reader);
			image->setImageIndex(y * 20 + x);
			image->setPosition(x * 29, y * 29);
		}
	}

	ai::NeuralNetwork network({ 784, 800, 10 },
	                          std::make_unique<ai::Sigmoid>());
	network.randomizeWeightsAndBiases(0);

	ai::NeuralNetworkCoach coach(
		network, std::make_unique<ai::DifferenceSquaredCostFunction>());

	ai::TrainingSet set;
	int             count = 0;
	for (const auto &img : reader.getImages()) {
		if (count++ > 1'000) break;
		std::vector<double> inputs;
		std::vector<double> outputs(10, 0);
		for (const auto &imgRow : img.pixels)
			for (auto pixel : imgRow) inputs.push_back((double) pixel / 255.0);
		outputs[img.label[0] - '0'] = 1.0;
		set.emplace_back(inputs, outputs);
	}

	for (int i = 0; i < 100; i++) {
		coach.train(set, 0.1);
		std::cout << coach.cost(set) << '\n';
	}
}
