//
// Created by mateusz on 10/2/23.
//

#pragma once

#include <Math/Vector2.hpp>

namespace mk {
	template<class T>
	class Rect {
	public:
		T left, top, width, height;

		[[nodiscard]] Math::Vector2<T> getPosition() const { return { left, top }; }

		[[nodiscard]] Math::Vector2<T> getSize() const { return { width, height }; }
	};

	typedef Rect<int>          RectI;
	typedef Rect<float>        RectF;
	typedef Rect<unsigned int> RectU;
}  // namespace mk
