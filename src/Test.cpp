//
// Created by mateusz on 9/16/23.
//

#include "Test.hpp"
#include <AI/Base/NeuralNetwork.hpp>
#include <AI/Coaches/NeuralNetworkCoach.hpp>

void run() {
  AI::NeuralNetwork network({4, 3, 5}, std::make_unique<AI::Sigmoid>());
  AI::NeuralNetworkCoach coach(network, std::make_unique<AI::DifferenceSquaredCostFunction>());
  AI::TrainingSet input = {
      AI::TrainingItem({1, 2, 3, 4}, {5, 5, 5, 5, 5})
  };
  coach.train(input, 0.1);
}
