//
// Created by mateusz on 9/16/23.
//

#include "NeuralNetwork.hpp"

#include <Random/Random.hpp>
#include <utility>

ai::NeuralNetwork::NeuralNetwork(
	std::vector<uint>                   newLayerSizes,
	std::unique_ptr<ActivatingFunction> activatingFunction
):
	  layerSizes(std::move(newLayerSizes)),
	  activatingFunction(std::move(activatingFunction)) {
	layers.emplace_back(layerSizes[0], 0, 0);
	for (uint i = 1; i < layerSizes.size(); i++)
		layers.emplace_back(layerSizes[i], layerSizes[i - 1], i);
}

ai::NeuralNetworkCalculationState
	ai::NeuralNetwork::getCalculations(const std::vector<double> &inputs
    ) const {
	ai::NeuralNetworkCalculationState state;

	state.activations.push_back(inputs);
	state.weightedInputs.emplace_back();

	for (uint layerId = 1; layerId < layers.size() - 1; layerId++) {
		state.weightedInputs.push_back(
			layers[layerId].calculate(state.activations.back())
		);
		state.activations.push_back(
			activatingFunction->calculate(state.weightedInputs.back())
		);
	}

	// for the last layer
	state.weightedInputs.push_back(
		layers[layers.size() - 1].calculate(state.activations.back())
	);
	state.activations.push_back(
		lastLayerActivatingFunction->calculate(state.weightedInputs.back())
	);

	return state;
}

double ai::NeuralNetwork::getWeight(
	uint layerIndex, uint nodeIndex, uint inputNodeIndex
) const {
	assert(layerIndex > 0 && layerIndex < layerSizes.size());
	assert(nodeIndex < layerSizes[layerIndex]);
	assert(inputNodeIndex < layerSizes[layerIndex - 1]);
	return layers[layerIndex].getWeight(nodeIndex, inputNodeIndex);
}

double ai::NeuralNetwork::getBias(uint layerIndex, uint nodeIndex) const {
	assert(layerIndex > 0 && layerIndex < layerSizes.size());
	assert(nodeIndex < layerSizes[layerIndex]);
	return layers[layerIndex].getBias(nodeIndex);
}

void ai::NeuralNetwork::setWeight(
	uint layerIndex, uint nodeIndex, uint inputNodeIndex, double value
) {
	layers[layerIndex].setWeight(nodeIndex, inputNodeIndex, value);
}

void ai::NeuralNetwork::setBias(uint layerIndex, uint nodeIndex, double value) {
	layers[layerIndex].setBias(nodeIndex, value);
}

ai::ActivatingFunction *ai::NeuralNetwork::getActivatingFunction() const {
	return activatingFunction.get();
}

const std::vector<uint> &ai::NeuralNetwork::getLayerSizes() const {
	return layerSizes;
}

ai::Layer &ai::NeuralNetwork::getLayer(uint index) { return layers[index]; }

void ai::NeuralNetwork::randomizeWeightsAndBiases(uint64_t seed) {
	mk::Random::initSeed(seed);
	for (auto &layer : layers) layer.randomizeWeightsAndBiases();
}

std::vector<ai::Layer> &ai::NeuralNetwork::getLayers() { return layers; }

const std::vector<ai::Layer> &ai::NeuralNetwork::getLayers() const {
	return layers;
}

std::vector<double>
	ai::NeuralNetwork::calculate(const std::vector<double> &inputs) const {
	return getCalculations(inputs).activations.back();
}

uint ai::NeuralNetwork::calculateBestIndex(const std::vector<double> &inputs
) const {
	auto   outputs  = calculate(inputs);
	double maxValue = 0.0;
	uint   maxIndex = 0;
	for (uint index = 0; index < outputs.size(); index++) {
		if (outputs[index] > maxValue) {
			maxValue = outputs[index];
			maxIndex = index;
		}
	}
	return maxIndex;
}

ai::ActivatingFunction *
	ai::NeuralNetwork::getLastLayerActivatingFunction() const {
	if (lastLayerActivatingFunction != nullptr)
		return lastLayerActivatingFunction.get();
	return getActivatingFunction();
}

ai::NeuralNetwork::NeuralNetwork(
	std::vector<uint>                   layerSizes,
	std::unique_ptr<ActivatingFunction> activatingFunction,
	std::unique_ptr<ActivatingFunction> customLastLayerActivatingFunction
):
	  ai::NeuralNetwork(std::move(layerSizes), std::move(activatingFunction)) {
	lastLayerActivatingFunction = std::move(customLastLayerActivatingFunction);
}
