//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_
#define AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_

namespace AI {
  class ActivatingFunction {
   public:
    virtual double calculate(double input) = 0;
  };
}


#endif //AI_FUN_SRC_AI_BASE_ACTIVATINGFUNCTION_HPP_
