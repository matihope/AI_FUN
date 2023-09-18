//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_AI_NEURALNETWORK_HPP_
#define AI_FUN_SRC_AI_NEURALNETWORK_HPP_

#include <vector>
#include <memory>
#include "Base/ActivatingFunction.hpp"
#include "Base/CostFunction.hpp"
#include "Base/Layer.hpp"
#include "NeuralNetworkCalculationState.hpp"
typedef unsigned int uint;

namespace AI {
  class NeuralNetwork {
   public:
    NeuralNetwork(std::vector<uint> layerSizes, std::unique_ptr<ActivatingFunction> activatingFunction);
    [[nodiscard]] NeuralNetworkCalculationState calculateOutputs(const std::vector<double>& inputs) const;

    [[nodiscard]] Layer &getLayer(uint index);
    [[nodiscard]] double getWeight(uint layerIndex, uint nodeIndex, uint inputNodeIndex) const;
    [[nodiscard]] double getBias(uint layerIndex, uint nodeIndex, uint inputNodeIndex) const;
    void setWeight(uint layerIndex, uint nodeIndex, uint inputNodeIndex, double value);
    void setBias(uint layerIndex, uint nodeIndex, uint inputNodeIndex, double value);
    [[nodiscard]] ActivatingFunction *getActivatingFunction() const;
    [[nodiscard]] const std::vector<uint> &getLayerSizes() const;

   private:
    std::vector<uint> layerSizes;
    std::unique_ptr<ActivatingFunction> activatingFunction;
    std::vector<Layer> layers;
  };
}

#endif //AI_FUN_SRC_AI_NEURALNETWORK_HPP_
