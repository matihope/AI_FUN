//
// Created by mateusz on 9/23/23.
//

#include "NeuralNetworkManager.hpp"

bool ai::NeuralNetworkManager::saveNeuralNetwork(const ai::NeuralNetwork &network, const std::string &filePath) {
	JsonBridge bridge;
	bridge.load(filePath);

	bridge.data["layerSizes"] = network.getLayerSizes();
	const auto &layers        = network.getLayers();
	for (uint layerIndex = 1; layerIndex < layers.size(); layerIndex++) {
		auto layerStr                    = std::to_string(layerIndex);
		bridge.data[layerStr]["biases"]  = layers[layerIndex].getBiases();
		bridge.data[layerStr]["weights"] = layers[layerIndex].getWeights();
	}
	bridge.data["activationFunction"] = network.getActivatingFunction()->getName();

	bridge.saveCurrentState();

	return true;
}

ai::NeuralNetwork ai::NeuralNetworkManager::loadNeuralNetwork(const std::string &filePath) {
	JsonBridge bridge;
	bridge.load(filePath);

	std::unique_ptr<ai::ActivatingFunction> activationFunction = std::make_unique<ai::ReLU>();
	if (bridge.data.contains("activationFunction")) {
		if (bridge.data["activationFunction"] == "ReLU")
			activationFunction = std::make_unique<ai::ReLU>();
		else if (bridge.data["activationFunction"] == "Sigmoid")
			activationFunction = std::make_unique<ai::Sigmoid>();
	}

	NeuralNetwork network(bridge.data["layerSizes"], std::move(activationFunction));

	for (uint layerIndex = 1; layerIndex < network.getLayers().size(); layerIndex++) {
		auto                             layerStr = std::to_string(layerIndex);
		std::vector<std::vector<double>> weights  = bridge.data[layerStr]["weights"];
		std::vector<double>              biases   = bridge.data[layerStr]["biases"];

		auto &layer = network.getLayer(layerIndex);
		for (uint node = 0; node < weights.size(); node++) {
			layer.setBias(node, biases[node]);

			for (uint input = 0; input < weights[node].size(); input++)
				layer.setWeight(node, input, weights[node][input]);
		}
	}

	return network;
}
