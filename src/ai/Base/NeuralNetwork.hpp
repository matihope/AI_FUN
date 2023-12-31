//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_AI_NEURALNETWORK_HPP_
#define AI_FUN_SRC_AI_NEURALNETWORK_HPP_

#include "ActivatingFunction.hpp"
#include "CostFunction.hpp"
#include "Layer.hpp"
#include "NeuralNetworkCalculationState.hpp"

#include <memory>
#include <vector>
typedef unsigned int uint;

namespace ai {
	class NeuralNetwork {
	public:
		NeuralNetwork(
			std::vector<uint>                   layerSizes,
			std::unique_ptr<ActivatingFunction> activatingFunction
		);
		NeuralNetwork(
			std::vector<uint>                   layerSizes,
			std::unique_ptr<ActivatingFunction> activatingFunction,
			std::unique_ptr<ActivatingFunction>
				customLastLayerActivatingFunction
		);

		[[nodiscard]] NeuralNetworkCalculationState
			getCalculations(const std::vector<double> &inputs) const;
		[[nodiscard]] std::vector<double>
						   calculate(const std::vector<double> &inputs) const;
		[[nodiscard]] uint calculateBestIndex(const std::vector<double> &inputs
		) const;

		[[nodiscard]] Layer                    &getLayer(uint index);
		[[nodiscard]] const std::vector<Layer> &getLayers() const;
		[[nodiscard]] std::vector<Layer>       &getLayers();
		[[nodiscard]] const std::vector<uint>  &getLayerSizes() const;

		[[nodiscard]] double getWeight(
			uint layerIndex, uint nodeIndex, uint inputNodeIndex
		) const;
		[[nodiscard]] double getBias(uint layerIndex, uint nodeIndex) const;
		void                 setWeight(
							uint layerIndex, uint nodeIndex, uint inputNodeIndex, double value
						);
		void setBias(uint layerIndex, uint nodeIndex, double value);

		[[nodiscard]] ActivatingFunction *getActivatingFunction() const;
		[[nodiscard]] ActivatingFunction *
			getLastLayerActivatingFunction() const;

		void randomizeWeightsAndBiases(uint64_t seed);

	private:
		std::vector<uint>                   layerSizes;
		std::unique_ptr<ActivatingFunction> activatingFunction,
			lastLayerActivatingFunction;
		std::vector<Layer> layers;
	};
}  // namespace ai

#endif  // AI_FUN_SRC_AI_NEURALNETWORK_HPP_
