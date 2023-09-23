//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_TEST_HPP_
#define AI_FUN_SRC_TEST_HPP_

#include "ai/Coaches/NeuralNetworkCoach.hpp"
#include "idx/Reader.hpp"

void run();
void run2();

ai::TrainingItem createItemFromIdxImage(const idx::Image &image);
ai::TrainingSet  createSetFromReader(const idx::Reader &reader, uint maxSize = -1);
void             teachImages();
void             testImages();

#endif  // AI_FUN_SRC_TEST_HPP_
