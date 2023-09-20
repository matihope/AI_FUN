//
// Created by mateusz on 9/18/23.
//

#ifndef AI_FUN_SRC_AI_BASE_NEURALNETWORKCALCULATIONSTATE_HPP_
#define AI_FUN_SRC_AI_BASE_NEURALNETWORKCALCULATIONSTATE_HPP_

#include <vector>
typedef unsigned int uint;

namespace ai {

	struct NeuralNetworkCalculationState {
		NeuralNetworkCalculationState() = default;
		explicit NeuralNetworkCalculationState(
			const std::vector<uint> &layerSizes);
		std::vector<std::vector<double>> activations;
		std::vector<std::vector<double>> weightedInputs;
	};

}  // namespace ai

#endif  // AI_FUN_SRC_AI_BASE_NEURALNETWORKCALCULATIONSTATE_HPP_
