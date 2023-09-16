//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_ENGINE_MATH_MATRIX_HPP_
#define AI_FUN_ENGINE_MATH_MATRIX_HPP_

#include <array>
#include "Base.hpp"

template<uint h, uint w>
class Matrix : public std::array<std::array<double, w>, h> {
 public:
  using std::array<std::array<double, w>, h>::array;

  template<uint x1, uint x2, uint x3>
  static Matrix<x1, x3> multiply(const Matrix<x1, x2>& a, const Matrix<x2, x3> &b) {
    Matrix<x1, x3> result{};
    for(int i = 0; i < x1; i++)
      for(int j = 0; j < x3; j++)
        for(int current = 0; current < x2; current++)
          result[i][j] += a[i][current] * b[current][j];
    return result;
  }
};

#endif //AI_FUN_ENGINE_MATH_MATRIX_HPP_
