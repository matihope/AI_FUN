//
// Created by mateusz on 9/17/23.
//

#include "Layer.hpp"

#include <cstdlib>

std::vector<double>
	Layer::calculate(const std::vector<double> &activations) const {
	assert(activations.size() == inputs);
	std::vector<double> output(nodes, 0);
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < inputs; j++)
			output[i] += weights[i][j] * activations[j] + biases[i][j];
	return output;
}

Layer::Layer(uint nodes, uint inputs): nodes(nodes), inputs(inputs) {
	weights.resize(nodes, std::vector<double>(inputs, 1));
	biases.resize(nodes, std::vector<double>(inputs, 1));
}

double Layer::getWeight(uint node, uint inputNode) const {
	return weights[node][inputNode];
}

double Layer::getBias(uint node, uint inputNode) const {
	return biases[node][inputNode];
}

void Layer::setWeight(uint node, uint inputNode, double newValue) {
	weights[node][inputNode] = newValue;
}

void Layer::setBias(uint node, uint inputNode, double newValue) {
	biases[node][inputNode] = newValue;
}

uint Layer::getInputNodesCount() const { return inputs; }

uint Layer::getNodesCount() const { return nodes; }

void Layer::randomizeWeightsAndBiases() {
	for (int node = 0; node < nodes; node++)
		for (int input = 0; input < inputs; input++) {
			biases[node][input]  = (double) std::rand() / RAND_MAX;
			weights[node][input] = (double) std::rand() / RAND_MAX;
		}
}
