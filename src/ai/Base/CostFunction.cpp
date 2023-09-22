//
// Created by mateusz on 9/17/23.
//

#include "CostFunction.hpp"

namespace ai {
	std::vector<double> CostFunction::calculate(const std::vector<double> &inputs, double correct) const {
		std::vector<double> outputs;
		for (auto d : inputs) outputs.push_back(calculate(d, correct));
		return outputs;
	}

	std::vector<double> CostFunction::derivative(const std::vector<double> &inputs, double correct) const {
		std::vector<double> outputs;
		for (auto d : inputs) outputs.push_back(derivative(d, correct));
		return outputs;
	}

	double DifferenceSquaredCostFunction::calculate(double input, double correct) const {
		return (correct - input) * (correct - input);
	}

	double DifferenceSquaredCostFunction::derivative(double input, double correct) const { return input - correct; }
}  // namespace ai
