//
// Created by mateusz on 9/17/23.
//

#ifndef AI_FUN_SRC_AI_COACHES_NEURALNETWORKCOACH_HPP_
#define AI_FUN_SRC_AI_COACHES_NEURALNETWORKCOACH_HPP_

#include "../Base/NeuralNetwork.hpp"
#include "LayerGradient.hpp"

namespace AI {

struct TrainingItem { std::vector<double> input, correctOutput; };
typedef std::vector<TrainingItem> TrainingSet;

class NeuralNetworkCoach {
 public:
  NeuralNetworkCoach(NeuralNetwork& neuralNetwork, std::unique_ptr<CostFunction> costFunction);
  void train(const TrainingSet& trainingSet, double trainingFactor);
 private:
  static void applyGradients(std::vector<LayerGradient> &gradients, double trainingFactor);

  void updateGradients(const TrainingItem &item, std::vector<LayerGradient> &gradients);
  void updateGradient(const std::vector<double> &nodeValues, LayerGradient &gradient);

  [[nodiscard]] double cost(const AI::TrainingItem &item) const;
  [[nodiscard]] double cost(const AI::TrainingSet &set) const;

  NeuralNetwork& neuralNetwork;
  std::unique_ptr<CostFunction> costFunction;
};
}

#endif //AI_FUN_SRC_AI_COACHES_NEURALNETWORKCOACH_HPP_
