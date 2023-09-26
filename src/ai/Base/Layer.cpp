//
// Created by mateusz on 9/17/23.
//

#include "Layer.hpp"

#include "Random/Random.hpp"

#include <cmath>
#include <cstdlib>

std::vector<double> Layer::calculate(const std::vector<double> &activations) const {
	assert(activations.size() == inputs);
	std::vector<double> output(nodes, 0);
	for (int i = 0; i < nodes; i++) {
		output[i] += biases[i];
		for (int j = 0; j < inputs; j++) output[i] += weights[i][j] * activations[j];
	}
	return output;
}

Layer::Layer(uint nodes, uint inputs, uint id): nodes(nodes), inputs(inputs), id(id) {
	weights.resize(nodes, std::vector<double>(inputs, 0));
	biases.resize(nodes, 0);
}

double Layer::getWeight(uint node, uint inputNode) const { return weights[node][inputNode]; }

double Layer::getBias(uint node) const { return biases[node]; }

void Layer::setWeight(uint node, uint inputNode, double newValue) { weights[node][inputNode] = newValue; }

void Layer::setBias(uint node, double newValue) { biases[node] = newValue; }

uint Layer::getInputNodesCount() const { return inputs; }

uint Layer::getNodesCount() const { return nodes; }

void Layer::randomizeWeightsAndBiases() {
	int A = 6;  // 2 if sigmoid, 6 otherwise
	for (int node = 0; node < nodes; node++)
		for (int input = 0; input < inputs; input++)
			weights[node][input] = mk::Random::getRandomNormalDist(0.0, 1.0) / inputs;
}

const std::vector<std::vector<double>> &Layer::getWeights() const { return weights; }

const std::vector<double> &Layer::getBiases() const { return biases; }

uint Layer::getId() const { return id; }
