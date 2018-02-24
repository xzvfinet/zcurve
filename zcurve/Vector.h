#pragma once

#include "Header.h"

namespace hj {
	template <typename T, int nDimensions>
	class Vector {
	public:
		Vector() {}
		Vector(T x, T y) : v{ x, y } {}
		Vector(T x, T y, T z) : v{ x, y, z } {}

		T operator[] (int ind) const {
			assert(ind < nDimensions);
			return v[ind];
		}
		void set(int i, T val) {
			this->v[i] = val;
		}
		Vector& operator+=(const Vector& rhs) {
			for (int i = 0; i < nDimensions; ++i) {
				v[i] += rhs[i];
			}
			return *this;
		}
		Vector& operator-=(const Vector& rhs) {
			for (int i = 0; i < nDimensions; ++i) {
				v[i] -= rhs[i];
			}
			return *this;
		}
		Vector& operator*=(const Vector& rhs) {
			for (int i = 0; i < nDimensions; ++i) {
				v[i] *= rhs[i];
			}
			return *this;
		}
		Vector& operator/=(const Vector &rhs) {
			for (int i = 0; i < nDimensions; ++i) {
				v[i] /= rhs[i];
			}
			return *this;
		}

		Vector operator+ (const Vector &rhs) const {
			Vector ret(*this);
			return ret += rhs;
		}
		Vector operator- (const Vector &rhs) const {
			Vector ret(*this);
			return ret -= rhs;
		}
		Vector operator* (const Vector &rhs) const {
			Vector ret(*this);
			return ret *= rhs;
		}
		Vector operator/ (const Vector &rhs) const {
			Vector ret(*this);
			return ret /= rhs;
		}

		template <typename U>
		Vector operator* (U rhs) const {
			Vector ret(*this);
			for (int i = 0; i < nDimensions; ++i) {
				ret.set(i, v[i] * rhs);
			}
			return ret;
		}
		template <typename U>
		Vector& operator*=(const U& rhs) {
			for (int i = 0; i < nDimensions; ++i) {
				v[i] *= rhs;
			}
			return *this;
		}

		std::string toString() const {
			auto str = std::to_string(v[0]);
			for (int i = 0; i < nDimensions; ++i) {
				str += ", " + v[i];
			}
			return str;
		}

		Vector<uint64_t, nDimensions> floor() const {
			Vector<uint64_t, nDimensions> ret;
			for (int i = 0; i < nDimensions; ++i) {
				ret.set(i, uint64_t(this->v[i]));
			}
			return ret;
		}

		template <typename U, int nD>
		friend std::ostream& operator<<(std::ostream&, const Vector<U, nD>&);

	private:
		std::array<T, nDimensions> v;
	};

	typedef Vector<float_t, 2> Vector2f;
	typedef Vector<uint64_t, 2> Vector2ui;

	typedef Vector<float_t, 3> Vector3f;
	typedef Vector<uint64_t, 3> Vector3ui;

	template <typename T, int nDimensions>
	std::ostream& operator<<(std::ostream& os, const hj::Vector<T, nDimensions>& v) {
		os << "[" << v[0];
		for (int i = 1; i < nDimensions; ++i) {
			os << ", " << v[i] << "]";
		}
		return os;
	}
}