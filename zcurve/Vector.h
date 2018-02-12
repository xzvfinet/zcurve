#pragma once

#include "Header.h"

template <typename T>
class Vector3 {
public:
	Vector3() : v{ T(),T(),T() } {}
	Vector3(T a, T b, T c) : v{ a, b, c } {}

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
		return std::to_string(v[0]);
	}

private:
	T v[3];
};

template <typename T>
std::ostream &operator<<(std::ostream &os, Vector3<T> const &rhs) {
	return os << rhs[0] << ", " << rhs[1] << ", " << rhs[2] << std::endl;
}

typedef Vector3<float_t> Vector3f;
typedef Vector3<uint64_t> Vector3ui;