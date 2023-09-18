//
// Created by mateusz on 9/16/23.
//

#include "NeuralNetwork.hpp"

AI::NeuralNetwork::NeuralNetwork(std::vector<uint> newLayerSizes,
                                 std::unique_ptr<ActivatingFunction> activatingFunction) : layerSizes(std::move(newLayerSizes)), activatingFunction(std::move(activatingFunction)) {
  for(uint i = 1; i < layerSizes.size(); i++) {
      layers.emplace_back(layerSizes[i - 1], layerSizes[i]);
  }
}

AI::NeuralNetworkCalculationState AI::NeuralNetwork::calculateOutputs(const std::vector<double>& inputs) const {
  AI::NeuralNetworkCalculationState state(layerSizes);

  state.activations.push_back(inputs);
  state.weightedInputs.emplace_back();

  for(const auto& layer: layers) {
    state.weightedInputs.push_back(layer.calculate(state.activations.back()));
    state.activations.push_back(activatingFunction->calculate(state.weightedInputs.back()));
  }

  return state;
}

double AI::NeuralNetwork::getWeight(uint layerIndex, uint nodeIndex, uint inputNodeIndex) const {
  assert(layerIndex > 0 && layerIndex < layerSizes.size());
  assert(nodeIndex < layerSizes[layerIndex]);
  assert(inputNodeIndex < layerSizes[layerIndex - 1]);
  return layers[layerIndex - 1].getWeight(nodeIndex, inputNodeIndex);
}

double AI::NeuralNetwork::getBias(uint layerIndex, uint nodeIndex, uint inputNodeIndex) const {
  assert(layerIndex > 0 && layerIndex < layerSizes.size());
  assert(nodeIndex < layerSizes[layerIndex]);
  assert(inputNodeIndex < layerSizes[layerIndex - 1]);
  return layers[layerIndex - 1].getBias(nodeIndex, inputNodeIndex);
}

void AI::NeuralNetwork::setWeight(uint layerIndex, uint nodeIndex, uint inputNodeIndex, double value) {
  layers[layerIndex - 1].setWeight(nodeIndex, inputNodeIndex, value);
}

void AI::NeuralNetwork::setBias(uint layerIndex, uint nodeIndex, uint inputNodeIndex, double value) {
  layers[layerIndex - 1].setWeight(nodeIndex, inputNodeIndex, value);
}

AI::ActivatingFunction *AI::NeuralNetwork::getActivatingFunction() const {
  return activatingFunction.get();
}

const std::vector<uint> &AI::NeuralNetwork::getLayerSizes() const {
  return layerSizes;
}

Layer &AI::NeuralNetwork::getLayer(uint index) {
  return layers[index];
}
