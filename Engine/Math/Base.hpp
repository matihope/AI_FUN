//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_ENGINE_MATH_BASE_HPP_
#define AI_FUN_ENGINE_MATH_BASE_HPP_

#include <cmath>

#define FLOAT_INFINITY 1000000000.f
#define INT_INFINITY 1000000000I
#define LL_INFINITY 1000000000000000000LL
#define EPS_ZERO 1e-12
#define M_PIf 3.14159265358979323846f	/* pi */
typedef unsigned int uint;

namespace Math {
  template<typename T>
  int sign(T val) {
    return (0 < val) - (val < 0);
  }

  template<typename T>
  bool isZero(T value, T EPSILON = EPS_ZERO) {
    return std::abs(value) <= EPSILON;
  }

  // makes while(value > range) value -= range
  // in an optimal way.
  float makeInRange(float value, float range);
  float radiansToDegrees(float radians);
  float degreesToRadians(float degrees);
}

#endif //AI_FUN_ENGINE_MATH_BASE_HPP_
