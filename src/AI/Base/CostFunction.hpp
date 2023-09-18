//
// Created by mateusz on 9/17/23.
//

#ifndef AI_FUN_SRC_AI_BASE_COSTFUNCTION_HPP_
#define AI_FUN_SRC_AI_BASE_COSTFUNCTION_HPP_

#include <vector>

namespace AI {
class CostFunction {
 public:
  virtual ~CostFunction() = default;
  [[nodiscard]] virtual double calculate(double input, double correct) const = 0;
  [[nodiscard]] std::vector<double> calculate(const std::vector<double> &inputs, double correct) const;
  [[nodiscard]] virtual double derivative(double input, double correct) const = 0;
  [[nodiscard]] std::vector<double> derivative(const std::vector<double> &inputs, double correct) const;
};

class DifferenceSquaredCostFunction : public CostFunction {
 public:
  [[nodiscard]] double calculate(double input, double correct) const override;
  [[nodiscard]] double derivative(double input, double correct) const override;
};

}


#endif //AI_FUN_SRC_AI_BASE_COSTFUNCTION_HPP_
