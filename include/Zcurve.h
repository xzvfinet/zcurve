#pragma once

#include "Header.h"
#include "Vector.h"

// Maximum number of cells
#define NUM_CELL_ZCURVE2D 1073741824  // 2^30 (30 bits * 2D = 60 bits)
#define NUM_CELL_ZCURVE3D 1048576     // 2^20 (20 bits * 3D = 60 bits)
#define NUM_CELL_ZCURVE5D 4096        // 2^12 (12 bits * 5D = 60 bits)
#define NUM_CELL_ZCURVE6D 1024        // 2^10 (10 bits * 6D = 60 bits)
#define NUM_CELL_ZCURVE8D 8           // 2^3  (3 bits  * 8D = 24 bits)

#define NUM_CELL_ZCURVE9D 16384       // 2^14 (14 bits * 9D = 126 bits)
#define NUM_CELL_ZCURVE12D 1024       // 2^10 (10 bits * 12D = 120 bits)
#define NUM_CELL_ZCURVE15D 256        // 2^10 ( 8 bits * 15D = 120 bits)

namespace hj {
class Zcurve {
    int K;
	const float eps = 1e-6f;

  public:
    Zcurve() {}

    template <typename T, int nDimensions>
    void order(const Vector<T, nDimensions>& pmin,
               const Vector<T, nDimensions>& pmax,
               std::vector<Vector<T, nDimensions>>& arr, int bits,
               const std::function<void(void)>& progressUpdate = 0) {
        this->K = bits;

        std::vector<std::pair<Vector<T, nDimensions>, uint128_t>> ordered(
            arr.size());
        for (auto i = 0u; i < arr.size(); ++i) {
            auto p = normalize(arr[i], pmin - eps, pmax + eps);
            uint128_t key = getMortonKey(p);
            ordered[i] = std::make_pair(arr[i], key);
        }

        std::sort(ordered.begin(), ordered.end(),
                  [&progressUpdate](
                      std::pair<Vector<T, nDimensions>, uint128_t>& lhs,
                      std::pair<Vector<T, nDimensions>, uint128_t>& rhs) {
                      if (progressUpdate) progressUpdate();
                      return lhs.second < rhs.second;
                  });

        for (auto i = 0u; i < arr.size(); ++i) {
            arr[i] = ordered[i].first;
        }
    }

    template <typename T, int nDimensions>
    uint128_t getMortonKey(Vector<T, nDimensions>& p) const {
        uint128_t result = 0;

        if (nDimensions == 2)
            p *= NUM_CELL_ZCURVE2D;
        else if (nDimensions == 3)
            p *= NUM_CELL_ZCURVE3D;
        else if (nDimensions == 5)
            p *= NUM_CELL_ZCURVE5D;
        else if (nDimensions == 6)
            p *= NUM_CELL_ZCURVE6D;
        else if (nDimensions == 8)
            p *= NUM_CELL_ZCURVE8D;
		else if (nDimensions == 9)
			p *= NUM_CELL_ZCURVE9D;
		else if (nDimensions == 12)
			p *= NUM_CELL_ZCURVE12D;
        else
            p = p * 0;

        Vector<uint128_t, nDimensions> n = p.floor();

        for (int i = 0; i < K; i++) {
            for (int j = 0; j < nDimensions; ++j) {
                result = result | ((n[j] & 1ULL << i) << (i + j));
            }
        }

        return result;
    }

    template <typename T, int nDimensions>
    Vector<T, nDimensions> normalize(const Vector<T, nDimensions>& point,
                                     const Vector<T, nDimensions>& pmin,
                                     const Vector<T, nDimensions>& pmax) const {
        auto origin = (point - pmin);
        auto size = (pmax - pmin);

        // [0,0] ~ [1,1]
        return (origin / size);
    }
};
}  // namespace hj