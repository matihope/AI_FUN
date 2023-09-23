//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_
#define AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_

#include <string>
#include <vector>

namespace ai {
	class ActivatingFunction {
	public:
		virtual ~ActivatingFunction()                                   = default;
		[[nodiscard]] virtual double      calculate(double input) const = 0;
		[[nodiscard]] std::vector<double> calculate(const std::vector<double> &inputs) const;
		[[nodiscard]] virtual double      derivative(double input) const = 0;
		[[nodiscard]] std::vector<double> derivative(const std::vector<double> &inputs) const;

		[[nodiscard]] virtual const std::string getName() const = 0;
	};

	class Sigmoid: public ActivatingFunction {
	public:
		[[nodiscard]] double calculate(double input) const override;
		[[nodiscard]] double derivative(double input) const override;

		[[nodiscard]] const std::string getName() const override { return "Sigmoid"; }
	};

	class ReLU: public ActivatingFunction {
	public:
		[[nodiscard]] double calculate(double input) const override;
		[[nodiscard]] double derivative(double input) const override;

		[[nodiscard]] const std::string getName() const override { return "ReLU"; }
	};
}  // namespace ai

#endif  // AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_
