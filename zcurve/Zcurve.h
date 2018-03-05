#pragma once

#include "Header.h"
#include "Vector.h"

#define NUM_CELL_ZCURVE2D 1073741824
#define NUM_CELL_ZCURVE3D 1048576
#define NUM_CELL_ZCURVE5D 4096
#define NUM_CELL_ZCURVE6D 1024
#define NUM_CELL_ZCURVE8D 8

namespace hj {
	class Zcurve
	{
		int K;

	public:
		Zcurve() {}

		void order2D(const Vector2f &pmin, const Vector2f &pmax,
			std::vector<Vector2f>& arr,
			int bits,
			const std::function< void(void)>& progressUpdate = 0) {
			this->K = bits;

			// this array cannot have reference as element type
			// because std::sort assumes the copy
			std::vector<std::pair<Vector2f, uint64_t>> ordered;
			ordered.reserve(arr.size());
			for (auto i = 0u; i < arr.size(); ++i) {
				auto p = normalize(arr[i], pmin, pmax);
				uint64_t key = getMortonKey(p);
				ordered.push_back({ arr[i], key });
			}

			std::sort(ordered.begin(), ordered.end(), [&progressUpdate](auto lhs, auto rhs) {
				if (progressUpdate)
					progressUpdate();
				return lhs.second < rhs.second;
			});

			for (auto i = 0u; i < arr.size(); ++i) {
				arr[i] = ordered[i].first;
			}
		}

		void order3D(const Vector3f &pmin, const Vector3f &pmax,
			std::vector<Vector3f>& arr,
			int bits,
			const std::function< void(void)>& progressUpdate) {
			this->K = bits;

			std::vector<std::pair<Vector3f, uint64_t>> ordered(arr.size());
			for (auto i = 0u; i < arr.size(); ++i) {
				auto p = normalize(arr[i], pmin, pmax);
				uint64_t key = getMortonKey(p);
				ordered[i] = std::make_pair(arr[i], key);
			}

			std::sort(ordered.begin(), ordered.end(), [&progressUpdate](auto lhs, auto rhs) {
				if (progressUpdate)
					progressUpdate();
				return lhs.second < rhs.second;
			});

			for (auto i = 0u; i < arr.size(); ++i) {
				arr[i] = ordered[i].first;
			}
		}

		template <typename T, int nDimensions>
		void order(const Vector<T, nDimensions> &pmin, const Vector<T, nDimensions> &pmax,
			std::vector<Vector<T, nDimensions>>& arr,
			int bits,
			const std::function< void(void)>& progressUpdate) {
			this->K = bits;

			std::vector<std::pair<Vector<T, nDimensions>, uint64_t>> ordered(arr.size());
			for (auto i = 0u; i < arr.size(); ++i) {
				auto p = normalize(arr[i], pmin, pmax);
				uint64_t key = getMortonKey(p);
				ordered[i] = std::make_pair(arr[i], key);
			}

			std::sort(ordered.begin(), ordered.end(), [&progressUpdate](auto lhs, auto rhs) {
				if (progressUpdate)
					progressUpdate();
				return lhs.second < rhs.second;
			});

			for (auto i = 0u; i < arr.size(); ++i) {
				arr[i] = ordered[i].first;
			}
		}

		template <typename T, int nDimensions>
		uint64_t getMortonKey(const Vector<T, nDimensions>& p) const {
			uint64_t result = 0;

			for (int i = 0; i < K; i++) {
				for (int j = 0; j < nDimensions; ++j) {
					result |= ((p[j] & 1ULL << i) << (i + j));
				}
			}

			return result;
		}

		template <typename T, int nDimensions>
		Vector<uint64_t, nDimensions> normalize(const Vector<T, nDimensions> &point, const Vector<T, nDimensions> &pmin, const Vector<T, nDimensions> &pmax) const {
			auto origin = (point - pmin);
			auto size = (pmax - pmin);
			auto n = (origin / size);

			if (nDimensions == 2) n *= NUM_CELL_ZCURVE2D;
			else if (nDimensions == 3) n *= NUM_CELL_ZCURVE3D;
			else if (nDimensions == 5) n *= NUM_CELL_ZCURVE5D;
			else if (nDimensions == 6) n *= NUM_CELL_ZCURVE6D;
			else if (nDimensions == 8) n *= NUM_CELL_ZCURVE8D;
			else n = n * 0;

			// floor
			return n.floor();
		}

	};
}