//
// Created by mateusz on 9/16/23.
//

#include "ActivatingFunction.hpp"

#include <cmath>

std::vector<double> ai::ActivatingFunction::calculate(const std::vector<double> &inputs) const {
	std::vector<double> outputs;
	for (auto d : inputs) outputs.push_back(calculate(d));
	return outputs;
}

std::vector<double> ai::ActivatingFunction::derivative(const std::vector<double> &inputs) const {
	std::vector<double> outputs;
	for (auto d : inputs) outputs.push_back(derivative(d));
	return outputs;
}

double ai::Sigmoid::calculate(double input) const { return 1.0 / (1.0 + std::pow(M_E, -input)); }

double ai::Sigmoid::derivative(double input) const { return calculate(input) * (1 - calculate(input)); }

double ai::ReLU::calculate(double input) const { return std::max(0.0, input); }

double ai::ReLU::derivative(double input) const {
	if (input < 0) return 0;
	return 1;
}
