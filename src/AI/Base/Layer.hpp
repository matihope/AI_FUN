//
// Created by mateusz on 9/17/23.
//

#ifndef AI_FUN_SRC_AI_BASE_LAYER_HPP_
#define AI_FUN_SRC_AI_BASE_LAYER_HPP_

#include <vector>
#include <cassert>

#define ASSERT_WITH_MSG(cond, msg) do \
{ if (!(cond)) { std::ostringstream str; str << msg; std::cerr << str.str(); std::abort(); } \
} while(0)

typedef unsigned int uint;

class Layer {
 public:
  Layer(uint input, uint nodes);
  [[nodiscard]] std::vector<double> calculate(const std::vector<double> &inputs) const;
  [[nodiscard]] double getWeight(uint node, uint inputNode) const;
  void setWeight(uint node, uint inputNode, double newValue);
  [[nodiscard]] double getBias(uint node, uint inputNode) const;
  void setBias(uint node, uint inputNode, double newValue);

  void randomizeWeightsAndBiases();
 private:
  uint input, nodes;
  std::vector<std::vector<double>> weights;
  std::vector<std::vector<double>> biases;
};

#endif //AI_FUN_SRC_AI_BASE_LAYER_HPP_