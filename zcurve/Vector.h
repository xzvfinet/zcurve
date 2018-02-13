#pragma once

#include "Header.h"

namespace hj {
	template <typename T>
	class Vector2 {
	public:
		Vector2() : v{ T(),T() } {}
		Vector2(T x, T y) : v{ x, y } {}

		T operator[] (int ind) const {
			assert(ind < 2);
			return v[ind];
		}
		Vector2<T> operator+ (const Vector2<T> &rhs) const {
			return Vector2<T>(v[0] + rhs[0], v[1] + rhs[1]);
		}
		Vector2<T> operator- (const Vector2<T> &rhs) const {
			return Vector2<T>(v[0] - rhs[0], v[1] - rhs[1]);
		}
		Vector2<T> operator* (const T rhs) const {
			return Vector2<T>(v[0] * rhs, v[1] * rhs);
		}
		Vector2<T> operator/ (const T rhs) const {
			return Vector2<T>(v[0] / rhs, v[1] / rhs);
		}
		Vector2<T> operator/ (const Vector2<T> &rhs) const {
			return Vector2<T>(v[0] / rhs[0], v[1] / rhs[1]);
		}

		std::string toString() const {
			return std::to_string(v[0]) + ", " + v[1];
		}

		Vector2<uint64_t> floor() const {
			return Vector2<uint64_t>(uint64_t(v[0]), uint64_t(v[1]));
		}

	private:
		T v[2];
	};

	typedef Vector2<float_t> Vector2f;
	typedef Vector2<uint64_t> Vector2ui;

	template <typename T>
	class Vector3 {
	public:
		Vector3() : v{ T(),T(),T() } {}
		Vector3(T x, T y, T z) : v{ x, y, z } {}

		T operator[] (int ind) const {
			assert(ind < 3);
			return v[ind];
		}
		Vector3<T> operator+ (const Vector3<T> &rhs) const {
			return Vector3<T>(v[0] + rhs[0], v[1] + rhs[1], v[2] + rhs[2]);
		}
		Vector3<T> operator- (const Vector3<T> &rhs) const {
			return Vector3<T>(v[0] - rhs[0], v[1] - rhs[1], v[2] - rhs[2]);
		}
		Vector3<T> operator* (const T rhs) const {
			return Vector3<T>(v[0] * rhs, v[1] * rhs, v[2] * rhs);
		}
		Vector3<T> operator/ (const T rhs) const {
			return Vector3<T>(v[0] / rhs, v[1] / rhs, v[2] / rhs);
		}
		Vector3<T> operator/ (const Vector3<T> &rhs) const {
			return Vector3<T>(v[0] / rhs[0], v[1] / rhs[1], v[2] / rhs[2]);
		}

		std::string toString() const {
			return std::to_string(v[0]) + ", " + v[1] + ", " + v[2];
		}

		Vector3<uint64_t> floor() const {
			return Vector3<uint64_t>(uint64_t(v[0]), uint64_t(v[1]), uint64_t(v[2]));
		}

	private:
		T v[3];
	};

	typedef Vector3<float_t> Vector3f;
	typedef Vector3<uint64_t> Vector3ui;
}

