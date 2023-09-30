//
// Created by mateusz on 9/17/23.
//

#ifndef AI_FUN_SRC_AI_BASE_LAYER_HPP_
#define AI_FUN_SRC_AI_BASE_LAYER_HPP_

#include <cassert>
#include <vector>

typedef unsigned int uint;

namespace ai {
	class Layer {
	public:
		Layer(uint nodes, uint inputs, uint id);
		[[nodiscard]] std::vector<double>                     calculate(const std::vector<double> &inputs) const;
		[[nodiscard]] double                                  getWeight(uint node, uint inputNode) const;
		void                                                  setWeight(uint node, uint inputNode, double newValue);
		[[nodiscard]] double                                  getBias(uint node) const;
		void                                                  setBias(uint node, double newValue);
		[[nodiscard]] const std::vector<std::vector<double>> &getWeights() const;
		[[nodiscard]] const std::vector<double>              &getBiases() const;

		void randomizeWeightsAndBiases();

		[[nodiscard]] uint getInputNodeCount() const;
		[[nodiscard]] uint getNodeCount() const;

		[[nodiscard]] uint getId() const;

	private:
		uint id;

		uint                             nodes, inputs;
		std::vector<std::vector<double>> weights;
		std::vector<double>              biases;
	};
}  // namespace ai

#endif  // AI_FUN_SRC_AI_BASE_LAYER_HPP_
