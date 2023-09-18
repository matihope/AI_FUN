//
// Created by mateusz on 9/18/23.
//

#include "NeuralNetworkCalculationState.hpp"

namespace AI {
NeuralNetworkCalculationState::NeuralNetworkCalculationState(const std::vector<uint> &layerSizes) {
  activations.emplace_back();
  weightedInputs.emplace_back();

  for(uint i = 1; i < layerSizes.size(); i++) {
    weightedInputs.emplace_back(layerSizes[i], 0);
    activations.emplace_back(layerSizes[i], 0);
  }
}
} // AI
