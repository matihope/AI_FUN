//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_ENGINE_MATH_GEOMETRY_HPP_
#define AI_FUN_ENGINE_MATH_GEOMETRY_HPP_

#include "Vector2f.hpp"

namespace Math {
	bool     doLinesIntersect(Vector2f lineAStart, Vector2f lineAEnd,
	                          Vector2f LineBStart, Vector2f LineBEnd);
	Vector2f findLineIntersection(Vector2f lineAStart, Vector2f lineAEnd,
	                              Vector2f LineBStart, Vector2f LineBEnd);
}

#endif  // AI_FUN_ENGINE_MATH_GEOMETRY_HPP_
