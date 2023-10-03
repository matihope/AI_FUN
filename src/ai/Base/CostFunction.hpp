//
// Created by mateusz on 9/17/23.
//

#ifndef AI_FUN_SRC_AI_BASE_COSTFUNCTION_HPP_
#define AI_FUN_SRC_AI_BASE_COSTFUNCTION_HPP_

#include <string>
#include <vector>

namespace ai {
	class CostFunction {
	public:
		virtual ~CostFunction() = default;
		[[nodiscard]] virtual double
			calculate(double input, double correct) const
			= 0;
		[[nodiscard]] std::vector<double> calculate(
			const std::vector<double> &inputs,
			const std::vector<double> &corrects
		) const;
		[[nodiscard]] virtual double
			derivative(double input, double correct) const
			= 0;
		[[nodiscard]] std::vector<double> derivative(
			const std::vector<double> &inputs,
			const std::vector<double> &corrects
		) const;

		[[nodiscard]] virtual const std::string getName() const = 0;
	};

	class DifferenceSquaredCostFunction: public CostFunction {
	public:
		[[nodiscard]] double
			calculate(double input, double correct) const override;
		[[nodiscard]] double
			derivative(double input, double correct) const override;

		[[nodiscard]] const std::string getName() const override {
			return "DifferenceSquaredCostFunction";
		}
	};

	class CrossEntropy: public CostFunction {
	public:
		[[nodiscard]] double
			calculate(double input, double correct) const override;
		[[nodiscard]] double
			derivative(double input, double correct) const override;

		[[nodiscard]] const std::string getName() const override {
			return "CrossEntropy";
		}
	};

}  // namespace ai


#endif  // AI_FUN_SRC_AI_BASE_COSTFUNCTION_HPP_
