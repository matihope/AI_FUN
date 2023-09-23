//
// Created by mateusz on 9/23/23.
//

#ifndef AI_FUN_SRC_AI_MODELLOADER_NEURALNETWORKMANAGER_HPP_
#define AI_FUN_SRC_AI_MODELLOADER_NEURALNETWORKMANAGER_HPP_

#include "Base/NeuralNetwork.hpp"
#include "JsonBridge/JsonBridge.hpp"

namespace ai {

	class NeuralNetworkManager {
	public:
		NeuralNetworkManager() = default;

		static bool          saveNeuralNetwork(const ai::NeuralNetwork &network, const std::string &filePath);
		static NeuralNetwork loadNeuralNetwork(const std::string &filePath);
	};
}  // namespace ai


#endif  // AI_FUN_SRC_AI_MODELLOADER_NEURALNETWORKMANAGER_HPP_
