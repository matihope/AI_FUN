//
// Created by mateusz on 9/16/23.
//

#include "NeuralNetwork.hpp"

ai::NeuralNetwork::NeuralNetwork(
	std::vector<uint>                   newLayerSizes,
	std::unique_ptr<ActivatingFunction> activatingFunction):
	layerSizes(std::move(newLayerSizes)),
	activatingFunction(std::move(activatingFunction)) {
	layers.emplace_back(layerSizes[0], 0);
	for (uint i = 1; i < layerSizes.size(); i++)
		layers.emplace_back(layerSizes[i], layerSizes[i - 1]);
}

ai::NeuralNetworkCalculationState ai::NeuralNetwork::calculateOutputs(
	const std::vector<double> &inputs) const {
	ai::NeuralNetworkCalculationState state(layerSizes);

	state.activations.push_back(inputs);
	state.weightedInputs.emplace_back();

	for (uint layerId = 1; layerId < layers.size(); layerId++) {
		state.weightedInputs.push_back(
			layers[layerId].calculate(state.activations.back()));
		state.activations.push_back(
			activatingFunction->calculate(state.weightedInputs.back()));
	}

	return state;
}

double ai::NeuralNetwork::getWeight(uint layerIndex, uint nodeIndex,
                                    uint inputNodeIndex) const {
	assert(layerIndex > 0 && layerIndex < layerSizes.size());
	assert(nodeIndex < layerSizes[layerIndex]);
	assert(inputNodeIndex < layerSizes[layerIndex - 1]);
	return layers[layerIndex].getWeight(nodeIndex, inputNodeIndex);
}

double ai::NeuralNetwork::getBias(uint layerIndex, uint nodeIndex,
                                  uint inputNodeIndex) const {
	assert(layerIndex > 0 && layerIndex < layerSizes.size());
	assert(nodeIndex < layerSizes[layerIndex]);
	assert(inputNodeIndex < layerSizes[layerIndex - 1]);
	return layers[layerIndex].getBias(nodeIndex, inputNodeIndex);
}

void ai::NeuralNetwork::setWeight(uint layerIndex, uint nodeIndex,
                                  uint inputNodeIndex, double value) {
	layers[layerIndex].setWeight(nodeIndex, inputNodeIndex, value);
}

void ai::NeuralNetwork::setBias(uint layerIndex, uint nodeIndex,
                                uint inputNodeIndex, double value) {
	layers[layerIndex].setWeight(nodeIndex, inputNodeIndex, value);
}

ai::ActivatingFunction *ai::NeuralNetwork::getActivatingFunction() const {
	return activatingFunction.get();
}

const std::vector<uint> &ai::NeuralNetwork::getLayerSizes() const {
	return layerSizes;
}

Layer &ai::NeuralNetwork::getLayer(uint index) { return layers[index]; }

void ai::NeuralNetwork::randomizeWeightsAndBiases(uint64_t seed) {
	std::srand(seed);
	for (auto &layer : layers) layer.randomizeWeightsAndBiases();
}
