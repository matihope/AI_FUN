//
// Created by mateusz on 9/17/23.
//

#include "CostFunction.hpp"

#include <cmath>

namespace ai {
	std::vector<double> CostFunction::calculate(
		const std::vector<double> &inputs, const std::vector<double> &corrects
	) const {
		std::vector<double> outputs;
		for (int i = 0; i < inputs.size(); i++)
			outputs.push_back(calculate(inputs[i], corrects[i]));
		return outputs;
	}

	std::vector<double> CostFunction::derivative(
		const std::vector<double> &inputs, const std::vector<double> &corrects
	) const {
		std::vector<double> outputs;
		for (int i = 0; i < inputs.size(); i++)
			outputs.push_back(derivative(inputs[i], corrects[i]));
		return outputs;
	}

	double DifferenceSquaredCostFunction::calculate(
		double input, double correct
	) const {
		return (correct - input) * (correct - input);
	}

	double DifferenceSquaredCostFunction::derivative(
		double input, double correct
	) const {
		return input - correct;
	}

	double CrossEntropy::calculate(double input, double correct) const {
		return -correct * std::log(input);
	}

	double CrossEntropy::derivative(double input, double correct) const {
		//		double x = input;
		//		double y = correct;
		//		if (x == 0 || x == 1) return 0;
		//		return (-x + y) / (x * (x - 1));
		// Softmax(input) * (1 - Softmax(input)) *


		return 1;
	}
}  // namespace ai
