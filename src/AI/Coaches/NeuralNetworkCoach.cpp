//
// Created by mateusz on 9/17/23.
//

#include "NeuralNetworkCoach.hpp"
#include "LayerGradient.hpp"

#include <utility>
#include <iostream>
AI::NeuralNetworkCoach::NeuralNetworkCoach(AI::NeuralNetwork& neuralNetwork,
                                           std::unique_ptr<CostFunction> costFunction) : neuralNetwork(neuralNetwork), costFunction(std::move(costFunction)) {

}



void AI::NeuralNetworkCoach::train(const TrainingSet& trainingSet, double trainingFactor) {

  // Create gradients
  std::vector<LayerGradient> gradients;
  for(uint i = 0; i < neuralNetwork.getLayerSizes().size(); i++)
    gradients.emplace_back(neuralNetwork.getLayer(i));

  // Make gradients sensible
  for(auto& item: trainingSet)
    updateGradients(item, gradients);

  // Apply them on the neural network
  applyGradients(gradients, trainingFactor / (double) trainingSet.size());
}

double AI::NeuralNetworkCoach::cost(const AI::TrainingItem &item) const {
//  auto calculationState = neuralNetwork.calculateOutputs(item.input);
//  double sum = 0;
//
//  for(uint i = 0; i < calculationState.activations.size(); i++)
//    sum += costFunction->calculate(outputs[i], item.correctOutput[i]);
//
//  return sum;
}
double AI::NeuralNetworkCoach::cost(const AI::TrainingSet &set) const {
  double totalCost = 0;

  for(const auto& item: set)
    totalCost += cost(item);

  return totalCost / (double) set.size();
}
void AI::NeuralNetworkCoach::updateGradients(const TrainingItem &item, std::vector<LayerGradient> &gradients) {
  auto outputs = neuralNetwork.calculateOutputs(item.input);

  // Last layer node values
  std::vector<double> nodeValues = calculateNodeValues(outputs, item);
  updateGradient(nodeValues, gradients.back());

  // Hidden layers node values
  for(int layerIndex = (int) neuralNetwork.getLayerSizes().size() - 2; layerIndex >= 0; layerIndex--) {
    nodeValues = std::move(calculateHiddenLayerNodeValues(layerIndex, outputs, nodeValues));
    updateGradient(nodeValues, gradients[layerIndex]);
  }
}

void AI::NeuralNetworkCoach::updateGradient(const std::vector<double> &nodeValues, LayerGradient &gradient) {
  for(uint node = 0; node < gradient.getLayer().getNodesCount(); node++) {
    for(uint inputNode = 0; inputNode < gradient.getLayer().getInputNodesCount(); inputNode++) {
      gradient.weightGradient[node][inputNode] += nodeValues[node] * gradient.getLayer().getWeight(node, inputNode);
      gradient.biasGradient[node][inputNode] += nodeValues[node];
    }
  }
}

void AI::NeuralNetworkCoach::applyGradients(std::vector<LayerGradient> &gradients, double trainingFactor) {
  for(auto &gradient: gradients)
    gradient.apply(trainingFactor);
}

std::vector<double> AI::NeuralNetworkCoach::calculateNodeValues(AI::NeuralNetworkCalculationState &outputs,
                                                                const AI::TrainingItem &item) {
  std::vector<double> nodeValues;
  for (int i = 0; i < neuralNetwork.getLayerSizes().size(); i++) {
    auto a = costFunction->derivative(outputs.activations.back()[i], item.correctOutput[i]);
    auto b = neuralNetwork.getActivatingFunction()->derivative(outputs.weightedInputs.back()[i]);
    nodeValues.push_back(a * b);
  }
  return nodeValues;
}

std::vector<double> AI::NeuralNetworkCoach::calculateHiddenLayerNodeValues(uint layerIndex,
                                                                           AI::NeuralNetworkCalculationState &outputs,
                                                                           std::vector<double> &nodeValues) const {
  std::vector<double> newNodeValues;

  for(uint nodeIndex = 0; nodeIndex < neuralNetwork.getLayerSizes()[layerIndex]; nodeIndex++) {
    double newNodeValue = 0.0;
    for(uint nodeIndexInPrevLayer = 0; nodeIndexInPrevLayer < neuralNetwork.getLayerSizes()[layerIndex + 1]; nodeIndexInPrevLayer++) {
      auto weight = neuralNetwork.getWeight(layerIndex + 1, nodeIndexInPrevLayer, nodeIndex);
      newNodeValue += weight * nodeValues[nodeIndexInPrevLayer];
    }
    newNodeValue *= neuralNetwork.getActivatingFunction()->derivative(outputs.weightedInputs[layerIndex][nodeIndex]);
    newNodeValues.push_back(newNodeValue);
  }

  return newNodeValues;
}
