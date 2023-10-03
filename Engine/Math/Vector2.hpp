//
// Created by mateusz on 9/16/23.
//

#ifndef AI_FUN_ENGINE_MATH_VECTOR2_HPP_
#define AI_FUN_ENGINE_MATH_VECTOR2_HPP_

#include <cmath>
#include <ostream>

namespace mk::Math {

	template<typename T>
	class Vector2 {
	public:
		T x = 0, y = 0;

		bool operator==(const Vector2<T> &rhs) const {
			return x == rhs.x && y == rhs.y;
		}

		Vector2<T> &operator+=(const Vector2<T> &rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Vector2<T> &operator-=(const Vector2<T> &rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		Vector2<T> &operator*=(const Vector2<T> &rhs) {
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		Vector2<T> &operator/=(const Vector2<T> &rhs) {
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		template<class X>
		Vector2<T> &operator*=(const X &rhs) {
			x *= rhs;
			y *= rhs;
			return *this;
		}

		template<class X>
		Vector2<T> &operator/=(const X &rhs) {
			x *= rhs;
			y *= rhs;
			return *this;
		}

		template<class X>
		Vector2<T> &operator+=(const X &rhs) {
			x += rhs;
			y += rhs;
			return *this;
		}

		template<class X>
		Vector2<T> &operator-=(const X &rhs) {
			x -= rhs;
			y -= rhs;
			return *this;
		}

		Vector2<T> operator+(const Vector2<T> &rhs) const {
			return { x + rhs.x, y + rhs.y };
		}

		Vector2<T> operator-(const Vector2<T> &rhs) const {
			return { x - rhs.x, y - rhs.y };
		}

		Vector2<T> operator*(const Vector2<T> &rhs) const {
			return { x * rhs.x, y * rhs.y };
		}

		Vector2<T> operator/(const Vector2<T> &rhs) const {
			return { x / rhs.x, y / rhs.y };
		}

		template<class X>
		Vector2<T> operator*(const X &rhs) const {
			return { x * rhs, y * rhs };
		}

		template<class X>
		Vector2<T> operator/(const X &rhs) const {
			return { x / rhs, y / rhs };
		}

		T length() const { return std::sqrt(x * x + y * y); }

		template<class X>
		Vector2<X> type() const {
			return { (X) x, (X) y };
		}

		template<class X>
		X as() const {
			return X(x, y);
		}

		friend std::ostream &
			operator<<(std::ostream &stream, const Vector2<T> &vector) {
			stream << vector.x << ", " << vector.y;
			return stream;
		}
	};

	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned int>;

	Vector2f normalizeVector(Vector2f vector);
	Vector2f rotateVector(Vector2f vector, float angleRads);
}  // namespace mk::Math
#endif  // AI_FUN_ENGINE_MATH_VECTOR2_HPP_
