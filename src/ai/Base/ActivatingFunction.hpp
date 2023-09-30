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
		virtual ~ActivatingFunction() = default;
		[[nodiscard]] virtual std::vector<double> calculate(const std::vector<double> &inputs) const;
		[[nodiscard]] virtual std::vector<double> derivative(const std::vector<double> &inputs) const;

		[[nodiscard]] virtual const std::string getName() const = 0;

	private:
		[[nodiscard]] virtual double calculate(double input) const  = 0;
		[[nodiscard]] virtual double derivative(double input) const = 0;
	};

	class Sigmoid: public ActivatingFunction {
		[[nodiscard]] double calculate(double input) const override;
		[[nodiscard]] double derivative(double input) const override;

	public:
		[[nodiscard]] const std::string getName() const override { return "Sigmoid"; }
	};

	class ReLU: public ActivatingFunction {
		[[nodiscard]] double calculate(double input) const override;
		[[nodiscard]] double derivative(double input) const override;

	public:
		[[nodiscard]] const std::string getName() const override { return "ReLU"; }
	};

	class SoftMax: public ActivatingFunction {
	public:
		[[nodiscard]] std::vector<double> calculate(const std::vector<double> &inputs) const override;
		[[nodiscard]] std::vector<double> derivative(const std::vector<double> &inputs) const override;

		[[nodiscard]] const std::string getName() const override { return "SoftMax"; }

	private:
		[[nodiscard]] double calculate(double input) const override;
		[[nodiscard]] double derivative(double input) const override;
	};
}  // namespace ai

#endif  // AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_
