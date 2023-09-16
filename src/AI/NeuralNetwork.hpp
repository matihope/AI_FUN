//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_AI_NEURALNETWORK_HPP_
#define AI_FUN_SRC_AI_NEURALNETWORK_HPP_

typedef unsigned int uint;
#include <vector>
#include "Base/ActivatingFunction.hpp"

namespace AI {
  class NeuralNetwork {
   public:
    NeuralNetwork(uint inputSize, uint outputSize, std::vector<uint> layerSizes, ActivatingFunction activatingFunction);
   private:

  };
}

#endif //AI_FUN_SRC_AI_NEURALNETWORK_HPP_
