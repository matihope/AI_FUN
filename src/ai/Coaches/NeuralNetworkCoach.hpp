//
// Created by mateusz on 9/17/23.
//

#ifndef AI_FUN_SRC_AI_COACHES_NEURALNETWORKCOACH_HPP_
#define AI_FUN_SRC_AI_COACHES_NEURALNETWORKCOACH_HPP_

#include "../Base/NeuralNetwork.hpp"
#include "LayerGradient.hpp"

namespace ai {

	struct TrainingItem {
		std::vector<double> input, correctOutput;
	};

	typedef std::vector<TrainingItem> TrainingSet;

	class NeuralNetworkCoach {
	public:
		NeuralNetworkCoach(NeuralNetwork &neuralNetwork, std::unique_ptr<CostFunction> costFunction);
		void   trainSingle(const TrainingSet &trainingSet, double learnRate);
		double train(TrainingSet trainingSet, double trainingFactor, uint batchSize, uint epochs, uint seed = 0);
		[[nodiscard]] double cost(const ai::TrainingItem &item) const;
		[[nodiscard]] double cost(const ai::TrainingSet &set) const;

	private:
		static void applyGradients(std::vector<LayerGradient> &gradients, double learnRate);

		void        updateGradients(const TrainingItem &item, std::vector<LayerGradient> &gradients);
		static void updateGradient(const std::vector<double> &nodeValues, LayerGradient &gradient,
		                           std::vector<double> &activations);


		NeuralNetwork                &neuralNetwork;
		std::unique_ptr<CostFunction> costFunction;
		std::vector<double>           calculateOutputLayerNodeValues(ai::NeuralNetworkCalculationState &outputs,
		                                                             const ai::TrainingItem            &item);
		std::vector<double> calculateHiddenLayerNodeValues(uint layerIndex, ai::NeuralNetworkCalculationState &outputs,
		                                                   std::vector<double> &nodeValues) const;
	};
}  // namespace ai

#endif  // AI_FUN_SRC_AI_COACHES_NEURALNETWORKCOACH_HPP_
