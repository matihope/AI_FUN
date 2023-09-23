//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_AI_NEURALNETWORK_HPP_
#define AI_FUN_SRC_AI_NEURALNETWORK_HPP_

#include "Base/ActivatingFunction.hpp"
#include "Base/CostFunction.hpp"
#include "Base/Layer.hpp"
#include "NeuralNetworkCalculationState.hpp"

#include <memory>
#include <vector>
typedef unsigned int uint;

namespace ai {
	class NeuralNetwork {
	public:
		NeuralNetwork(std::vector<uint> layerSizes, std::unique_ptr<ActivatingFunction> activatingFunction);
		[[nodiscard]] NeuralNetworkCalculationState calculateOutputs(const std::vector<double> &inputs) const;

		[[nodiscard]] Layer              &getLayer(uint index);
		[[nodiscard]] double              getWeight(uint layerIndex, uint nodeIndex, uint inputNodeIndex) const;
		[[nodiscard]] double              getBias(uint layerIndex, uint nodeIndex) const;
		void                              setWeight(uint layerIndex, uint nodeIndex, uint inputNodeIndex, double value);
		void                              setBias(uint layerIndex, uint nodeIndex, double value);
		[[nodiscard]] ActivatingFunction *getActivatingFunction() const;
		[[nodiscard]] const std::vector<uint> &getLayerSizes() const;

		void randomizeWeightsAndBiases(uint64_t seed);

	private:
		std::vector<uint>                   layerSizes;
		std::unique_ptr<ActivatingFunction> activatingFunction;
		std::vector<Layer>                  layers;
	};
}  // namespace ai

#endif  // AI_FUN_SRC_AI_NEURALNETWORK_HPP_
