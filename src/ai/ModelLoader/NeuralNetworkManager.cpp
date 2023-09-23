//
// Created by mateusz on 9/23/23.
//

#include "NeuralNetworkManager.hpp"

bool ai::NeuralNetworkManager::saveNeuralNetwork(const ai::NeuralNetwork &network, const std::string &filePath) {
	JsonBridge bridge;
	bridge.load(filePath);

	bridge.data["layerSizes"] = { network.getLayerSizes() };
	bridge.data["biases"]     = {};
}
