//
// Created by mateusz on 9/18/23.
//

#include "LayerGradient.hpp"

namespace ai {
	LayerGradient::LayerGradient(Layer &layer): layer(layer) {
		weightGradient.resize(
			layer.getNodesCount(),
			std::vector<double>(layer.getInputNodesCount(), 0));
		biasGradient.resize(layer.getNodesCount(),
		                    std::vector<double>(layer.getInputNodesCount(), 0));
	}

	void LayerGradient::apply(double trainingFactor) {
		for (uint node = 0; node < layer.getNodesCount(); node++) {
			for (uint inputNode = 0; inputNode < layer.getInputNodesCount();
			     inputNode++) {
				auto weight = layer.getWeight(node, inputNode);
				auto bias   = layer.getBias(node, inputNode);
				layer.setWeight(
					node, inputNode,
					weight - weightGradient[node][inputNode] * trainingFactor);
				layer.setBias(
					node, inputNode,
					bias - biasGradient[node][inputNode] * trainingFactor);
			}
		}
	}

	Layer &LayerGradient::getLayer() { return layer; }
}  // namespace ai
