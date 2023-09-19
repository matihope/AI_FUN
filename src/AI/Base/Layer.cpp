//
// Created by mateusz on 9/17/23.
//

#include "Layer.hpp"
#include <cstdlib>

std::vector<double> Layer::calculate(const std::vector<double> &inputs) const {
  assert(inputs.size() == input);
  std::vector<double> output(nodes, 0);
  for(int i = 0; i < nodes; i++)
    for(int j = 0; j < input; j++)
      output[i] += weights[i][j] * inputs[j] + biases[i][j];
  return output;
}

Layer::Layer(uint nodes, uint input) : nodes(nodes), input(input) {
  weights.resize(nodes, std::vector<double>(input, 0));
  biases.resize(nodes, std::vector<double>(input, 0));
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
uint Layer::getInputNodesCount() const {
  return input;
}
uint Layer::getNodesCount() const {
  return nodes;
}
