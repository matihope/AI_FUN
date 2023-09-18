//
// Created by mateusz on 9/18/23.
//

#ifndef AI_FUN_SRC_AI_COACHES_LAYERGRADIENT_HPP_
#define AI_FUN_SRC_AI_COACHES_LAYERGRADIENT_HPP_

#include <vector>
#include "Base/Layer.hpp"

typedef unsigned int uint;

namespace AI {

class LayerGradient {
 public:
  explicit LayerGradient(Layer &layer);
  std::vector<std::vector<double>> weightGradient, biasGradient;
  void apply(double trainingFactor);
  Layer &getLayer();
 private:
  Layer &layer;
};

} // AI

#endif //AI_FUN_SRC_AI_COACHES_LAYERGRADIENT_HPP_
