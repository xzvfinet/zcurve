#pragma once

#include "Header.h"

namespace hj {
template <typename T, int nDimensions>
class Vector {
  public:
    Vector() {}
    template <typename... Args>
    Vector(T x) {
        for (int i = 0; i < nDimensions; ++i) v[i] = x;
    }
    Vector(T x, T y) : v{x, y} {}
    Vector(T x, T y, T z) : v{x, y, z} {}
    Vector(T x, T y, T z, T a, T b) : v{x, y, z, a, b} {}

#ifdef PBRT_CORE_PBRT_H
    Vector(pbrt::Point2<T> p) : v{p.x, p.y} {}
    template <typename U>
    Vector(pbrt::Point2<U> p) : v{T(p.x), T(p.y)} {}

    Vector(pbrt::Point3<T> p) : v{p.x, p.y, p.z} {}
    template <typename U>
    Vector(pbrt::Point3<U> p) : v{T(p.x), T(p.y), T(p.z)} {}

    Vector(pbrt::Point2<T> p1, pbrt::Point3<T> p2)
        : v{p1.x, p1.y, p2.x, p2.y, p2.z} {}
    template <typename U>
    Vector(pbrt::Point2<U> p1, pbrt::Point3<U> p2)
        : v{T(p1.x), T(p1.y), T(p2.x), T(p2.y), T(p2.z)} {}
#endif

    T operator[](int ind) const {
        assert(ind < nDimensions);
        return v[ind];
    }
    void set(int i, T val) { this->v[i] = val; }
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
    Vector& operator/=(const Vector& rhs) {
        for (int i = 0; i < nDimensions; ++i) {
            v[i] /= rhs[i];
        }
        return *this;
    }

    Vector operator+(const Vector& rhs) const {
        Vector ret(*this);
        return ret += rhs;
    }
    Vector operator+(const T& rhs) const {
        Vector ret(*this);
        return ret += Vector(rhs);
    }
    Vector operator-(const Vector& rhs) const {
        Vector ret(*this);
        return ret -= rhs;
    }
    Vector operator-(const T rhs) const {
        Vector ret(*this);
        return ret -= Vector(rhs);
    }
    Vector operator*(const Vector& rhs) const {
        Vector ret(*this);
        return ret *= rhs;
    }
    Vector operator/(const Vector& rhs) const {
        Vector ret(*this);
        return ret /= rhs;
    }

    template <typename U>
    Vector operator*(U rhs) const {
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

    Vector<uint128_t, nDimensions> floor() const {
        Vector<uint128_t, nDimensions> ret;
        for (int i = 0; i < nDimensions; ++i) {
            ret.set(i, uint128_t(this->v[i]));
        }
        return ret;
    }

    template <typename U, int nD>
    friend std::ostream& operator<<(std::ostream&, const Vector<U, nD>&);

  private:
    std::array<T, nDimensions> v;
};

typedef Vector<float, 2> Vector2f;
typedef Vector<uint128_t, 2> Vector2ui;

typedef Vector<float, 3> Vector3f;
typedef Vector<uint128_t, 3> Vector3ui;

typedef Vector<float, 5> Vector5f;
typedef Vector<uint128_t, 5> Vector5ui;

template <typename T, int nDimensions>
std::ostream& operator<<(std::ostream& os,
                         const hj::Vector<T, nDimensions>& v) {
    os << "[" << v[0];
    for (int i = 1; i < nDimensions; ++i) {
        os << ", " << v[i];
    }
    os << "]" << std::endl;
    return os;
}
}  // namespace hj