//
// Created by mateusz on 9/18/23.
//

#include "LayerGradient.hpp"

namespace ai {
	LayerGradient::LayerGradient(Layer &layer): layer(layer) {
		weightGradient.resize(layer.getNodesCount(), std::vector<double>(layer.getInputNodesCount(), 0));
		biasGradient.resize(layer.getNodesCount(), 0);
	}

	void LayerGradient::apply(double learnRate, double lambda) {
		for (uint node = 0; node < layer.getNodesCount(); node++) {
			for (uint inputNode = 0; inputNode < layer.getInputNodesCount(); inputNode++) {
				auto weight = layer.getWeight(node, inputNode);

				layer.setWeight(node, inputNode,
				                weight - (weightGradient[node][inputNode] - weight * lambda) * learnRate);
			}
			auto bias = layer.getBias(node);
			layer.setBias(node, bias - (biasGradient[node] - bias * lambda) * learnRate);
		}
	}

	Layer &LayerGradient::getLayer() { return layer; }
}  // namespace ai
