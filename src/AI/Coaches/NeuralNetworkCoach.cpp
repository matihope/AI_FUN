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
  applyGradients(gradients, trainingFactor);
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
  std::vector<double> nodeValues;
  for (int i = 0; i < neuralNetwork.getLayerSizes().size(); i++) {
    auto a = costFunction->derivative(outputs.activations.back()[i], item.correctOutput[i]);
    auto b = neuralNetwork.getActivatingFunction()->derivative(outputs.weightedInputs.back()[i]);
    nodeValues.push_back(a * b);
  }
  updateGradient(nodeValues, gradients.back());

  for(int layerIndex = (int) neuralNetwork.getLayerSizes().size() - 2; layerIndex >= 0; layerIndex--) {
    std::vector<double> newNodeValues;
    for(uint nodeIndex = 0; nodeIndex < neuralNetwork.getLayerSizes()[layerIndex]; nodeIndex++) {
      for(uint nodeIndexInPrevLayer = 0; nodeIndexInPrevLayer < neuralNetwork.getLayerSizes()[layerIndex + 1]; nodeIndexInPrevLayer++) {
        auto weight = neuralNetwork.getWeight(layerIndex + 1, nodeIndexInPrevLayer, nodeIndex);
        newNodeValues.push_back(nodeValues[nodeIndexInPrevLayer] * weight);
      }
    }
    nodeValues = std::move(newNodeValues);
    updateGradient(nodeValues, gradients[layerIndex]);
  }
}

void AI::NeuralNetworkCoach::updateGradient(const std::vector<double> &nodeValues, LayerGradient &gradient) {

}
void AI::NeuralNetworkCoach::applyGradients(std::vector<LayerGradient> &gradients, double trainingFactor) {
  for(auto &gradient: gradients)
    gradient.apply(trainingFactor);
}
