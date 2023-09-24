//
// Created by mateusz on 9/23/23.
//

#ifndef AI_FUN_SRC_IDXDIGITTRAINER_HPP_
#define AI_FUN_SRC_IDXDIGITTRAINER_HPP_

#include "ai/Coaches/NeuralNetworkCoach.hpp"
#include "idx/Reader.hpp"

class IdxDigitTrainer {
public:
	IdxDigitTrainer() = delete;

	static ai::TrainingItem createItemFromIdxImage(const idx::Image &image);
	static ai::TrainingSet  createSetFromReader(const idx::Reader &reader, uint maxSize = -1);

	static void teachImages(const std::string &modelPath);
	static void testImages(const std::string &modelPath);
	static void moreTrainer();
};


#endif  // AI_FUN_SRC_IDXDIGITTRAINER_HPP_
