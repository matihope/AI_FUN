//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_
#define AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_

#include <vector>
namespace AI {
  class ActivatingFunction {
   public:
    virtual ~ActivatingFunction() = default;
    [[nodiscard]] virtual double calculate(double input) const = 0;
    [[nodiscard]] std::vector<double> calculate(const std::vector<double> &inputs) const;
    [[nodiscard]] virtual double derivative(double input) const = 0;
    [[nodiscard]] std::vector<double> derivative(const std::vector<double> &inputs) const;
  };
class Sigmoid : public ActivatingFunction {
 public:
  [[nodiscard]] double calculate(double input) const override;
  [[nodiscard]] double derivative(double input) const override;
};
}

#endif //AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_
