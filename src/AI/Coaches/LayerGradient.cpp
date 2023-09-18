//
// Created by mateusz on 9/18/23.
//

#include "LayerGradient.hpp"

namespace AI {
LayerGradient::LayerGradient(Layer &layer): layer(layer) {

}
void LayerGradient::apply(double trainingFactor) {

}
Layer &LayerGradient::getLayer() {
  return layer;
}
} // AI
