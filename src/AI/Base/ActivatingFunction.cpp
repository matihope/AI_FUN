//
// Created by mateusz on 9/16/23.
//

#include "ActivatingFunction.hpp"
#include <cmath>

std::vector<double> AI::ActivatingFunction::calculate(const std::vector<double> &inputs) const {
  std::vector<double> outputs;
  for(auto d: inputs)
    outputs.push_back(calculate(d));
  return outputs;
}

std::vector<double> AI::ActivatingFunction::derivative(const std::vector<double> &inputs) const {
  std::vector<double> outputs;
  for(auto d: inputs)
    outputs.push_back(derivative(d));
  return outputs;
}

double AI::Sigmoid::calculate(double input) const {
  return 1.0 / (1.0 + std::pow(M_E, -input));
}
double AI::Sigmoid::derivative(double input) const {
  return calculate(input) * calculate(1 - input);
}
