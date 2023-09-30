//
// Created by mateusz on 9/17/23.
//

#include "NeuralNetworkCoach.hpp"

#include "../../idx/Reader.hpp"
#include "LayerGradient.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <thread>
#include <utility>

namespace ai {

	ai::NeuralNetworkCoach::NeuralNetworkCoach(ai::NeuralNetwork            &neuralNetwork,
	                                           std::unique_ptr<CostFunction> costFunction):
		neuralNetwork(neuralNetwork),
		costFunction(std::move(costFunction)) {
		mut.push_back({});
		for (uint layerId = 1; layerId < neuralNetwork.getLayerSizes().size(); layerId++)
			mut.push_back(std::vector<std::mutex>(neuralNetwork.getLayerSizes()[layerId]));
	}

	void ai::NeuralNetworkCoach::trainSingle(const TrainingSet &trainingSet, double learnRate) {
		// Create gradients
		gradients.clear();
		for (uint i = 0; i < neuralNetwork.getLayerSizes().size(); i++)
			gradients.emplace_back(neuralNetwork.getLayer(i));

		std::vector<std::thread> threads;

		// Make gradients sensible
		for (const auto &item : trainingSet) threads.emplace_back(&ai::NeuralNetworkCoach::updateGradients, this, item);

		for (auto &thr : threads) thr.join();

		//		for (const auto &item : trainingSet) updateGradients(item);


		// Apply them on the neural network
		//		std::vector<ai::Layer> layers = neuralNetwork.getLayers();
		//		double initial = cost(trainingSet);
		applyGradients(gradients, learnRate / (double) trainingSet.size());
		//		std::cerr << "Change: " << cost(trainingSet) - initial << '\n';

		//		testImages(neuralNetwork);

		//		for (int layerId = 1; layerId < layers.size(); layerId++) {
		//			auto &layer = neuralNetwork.getLayers()[layerId];
		//			for (int nodeId = 0; nodeId < layer.getNodeCount(); ++nodeId)
		//				std::cout << layerId << "," << nodeId
		//						  << ", diff in bias: " << layers[layerId].getBias(nodeId) - layer.getBias(nodeId) <<
		//'\n';
		//		}
	}

	void ai::NeuralNetworkCoach::updateGradients(const TrainingItem &item) {
		auto outputs    = neuralNetwork.getCalculations(item.input);
		auto layerCount = neuralNetwork.getLayerSizes().size();

		// Last layer node values
		std::vector<double> nodeValues = calculateOutputLayerNodeValues(outputs, item);
		updateGradient(nodeValues, gradients.back(), outputs.activations[layerCount - 2]);

		// Hidden layers node values
		for (int layerIndex = layerCount - 2; layerIndex > 0; layerIndex--) {
			nodeValues = std::move(calculateHiddenLayerNodeValues(layerIndex, outputs, nodeValues));
			updateGradient(nodeValues, gradients[layerIndex], outputs.activations[layerIndex - 1]);
		}
	}

	void ai::NeuralNetworkCoach::updateGradient(const std::vector<double> &nodeValues, LayerGradient &gradient,
	                                            std::vector<double> &activations) {
		for (uint node = 0; node < gradient.getLayer().getNodeCount(); node++) {
			mut[gradient.getLayer().getId()][node].lock();
			for (uint inputNode = 0; inputNode < gradient.getLayer().getInputNodeCount(); inputNode++)
				gradient.weightGradient[node][inputNode] += nodeValues[node] * activations[inputNode];
			gradient.biasGradient[node] += nodeValues[node];
			mut[gradient.getLayer().getId()][node].unlock();
		}
	}

	void ai::NeuralNetworkCoach::applyGradients(std::vector<LayerGradient> &gradients, double learnRate) {
		for (auto &gradient : gradients) gradient.apply(learnRate);
	}

	std::vector<double>
		ai::NeuralNetworkCoach::calculateOutputLayerNodeValues(ai::NeuralNetworkCalculationState &outputs,
	                                                           const ai::TrainingItem            &item) {
		auto activatingFunction = neuralNetwork.getLastLayerActivatingFunction();

		std::vector<double> nodeValues;


		if (activatingFunction->getName() == "SoftMax" && costFunction->getName() == "CrossEntropy") {
			for (int i = 0; i < neuralNetwork.getLayerSizes().back(); i++)
				nodeValues.push_back(outputs.activations.back()[i] - item.correctOutput[i]);
			return nodeValues;
		}

		auto activatingFunctionDerivatives = activatingFunction->derivative(outputs.weightedInputs.back());
		auto costFunctionDerivatives       = costFunction->derivative(outputs.activations.back(), item.correctOutput);

		for (int i = 0; i < neuralNetwork.getLayerSizes().back(); i++)
			nodeValues.push_back(activatingFunctionDerivatives[i] * costFunctionDerivatives[i]);
		return nodeValues;
	}

	std::vector<double> ai::NeuralNetworkCoach::calculateHiddenLayerNodeValues(
		uint layerIndex, ai::NeuralNetworkCalculationState &outputs, std::vector<double> &nodeValues) const {
		std::vector<double> newNodeValues;

		auto derivatives = neuralNetwork.getActivatingFunction()->derivative(outputs.weightedInputs[layerIndex]);

		for (uint nodeIndex = 0; nodeIndex < neuralNetwork.getLayerSizes()[layerIndex]; nodeIndex++) {
			double newNodeValue = 0.0;
			for (uint nodeIndexInPrevLayer = 0; nodeIndexInPrevLayer < neuralNetwork.getLayerSizes()[layerIndex + 1];
			     nodeIndexInPrevLayer++) {
				auto weight = neuralNetwork.getWeight(layerIndex + 1, nodeIndexInPrevLayer, nodeIndex);
				newNodeValue += weight * nodeValues[nodeIndexInPrevLayer];
			}
			newNodeValues.push_back(newNodeValue * derivatives[nodeIndex]);
		}

		return newNodeValues;
	}

	double ai::NeuralNetworkCoach::cost(const ai::TrainingItem &item) const {
		auto   calculationState = neuralNetwork.getCalculations(item.input);
		double sum              = 0;

		for (uint i = 0; i < calculationState.activations.size(); i++)
			sum += costFunction->calculate(calculationState.activations.back()[i], item.correctOutput[i]);

		return sum;
	}

	double ai::NeuralNetworkCoach::cost(const ai::TrainingSet &set) const {
		double totalCost = 0;

		for (const auto &item : set) totalCost += cost(item);

		return totalCost / (double) set.size();
	}

	double NeuralNetworkCoach::train(TrainingSet trainingSet, double trainingFactor, uint batchSize, uint epochs,
	                                 uint seed) {
		std::shuffle(trainingSet.begin(), trainingSet.end(), std::default_random_engine(seed));

		std::vector<TrainingSet> batches;
		for (uint batchId = 0; batchId < trainingSet.size() / batchSize; ++batchId) {
			TrainingSet batch;
			for (uint i = 0; i < batchSize; i++) {
				uint finalIndex = batchId * batchSize + i;
				if (finalIndex >= trainingSet.size()) break;
				batch.push_back(trainingSet[finalIndex]);
			}
			batches.push_back(std::move(batch));
		}

		std::cerr << cost(trainingSet) << '\n';
		auto lastCost = 0.0;
		for (uint epoch = 0; epoch < epochs; epoch++) {
			for (const auto &batch : batches) trainSingle(batch, trainingFactor);
			lastCost = cost(trainingSet);
			std::cerr << "Epoch: " << epoch << ", avgCost: " << lastCost << '\n';
		}

		return lastCost;
	}
}  // namespace ai
