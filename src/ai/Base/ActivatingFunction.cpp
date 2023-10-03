//
// Created by mateusz on 9/16/23.
//

#include "ActivatingFunction.hpp"

#include <cmath>

std::vector<double>
	ai::ActivatingFunction::calculate(const std::vector<double> &inputs) const {
	std::vector<double> outputs;
	for (auto d : inputs) outputs.push_back(calculate(d));
	return outputs;
}

std::vector<double>
	ai::ActivatingFunction::derivative(const std::vector<double> &inputs
    ) const {
	std::vector<double> outputs;
	for (auto d : inputs) outputs.push_back(derivative(d));
	return outputs;
}

double ai::Sigmoid::calculate(double input) const {
	return 1.0 / (1.0 + std::pow(M_E, -input));
}

double ai::Sigmoid::derivative(double input) const {
	return calculate(input) * (1 - calculate(input));
}

double ai::ReLU::calculate(double input) const { return std::max(0.0, input); }

double ai::ReLU::derivative(double input) const {
	if (input < 0) return 0;
	return 1;
}

double ai::SoftMax::calculate(double input) const {
	// division happens in other function
	return std::exp(input);
}

std::vector<double> ai::SoftMax::calculate(const std::vector<double> &inputs
) const {
	double denominator = 0.0;
	for (auto input : inputs) denominator += std::exp(input);

	std::vector<double> outputs;
	for (auto input : inputs) outputs.push_back(calculate(input) / denominator);
	return outputs;
}

//(ei/(ei + ej + ek))'' = ei * ((ei + ej + ek) - ei) / (ei + ej + ek)^2
//	= (ei / (ei + ej + ek)) * ()

double ai::SoftMax::derivative(double input) const {
	return input * (1.0 - input);
}

std::vector<double> ai::SoftMax::derivative(const std::vector<double> &inputs
) const {
	auto calculations = calculate(inputs);

	std::vector<double> outputs;
	for (auto input : calculations) outputs.push_back(derivative(input));
	return outputs;
}
