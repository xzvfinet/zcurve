#pragma once

#include "Header.h"
#include "Vector.h"

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

			std::vector<std::pair<Vector2f, uint64_t>> ordered(arr.size());
			for (auto i = 0u; i < arr.size(); ++i) {
				auto p = normalize<Vector2ui>(arr[i], pmin, pmax);
				uint64_t key = getMortonKey2D(p);
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

		void order3D(const Vector3f &pmin, const Vector3f &pmax,
			std::vector<Vector3f>& arr,
			int bits,
			const std::function< void(void)>& progressUpdate) {
			this->K = bits;

			std::vector<std::pair<Vector3f, uint64_t>> ordered(arr.size());
			for (auto i = 0u; i < arr.size(); ++i) {
				auto p = normalize<Vector3ui>(arr[i], pmin, pmax);
				uint64_t key = getMortonKey3D(p);
				ordered[i] = std::make_pair(arr[i], key);
			}

			std::sort(ordered.begin(), ordered.end(), [&progressUpdate](auto lhs, auto rhs) {
				progressUpdate();
				return lhs.second < rhs.second;
			});

			for (auto i = 0u; i < arr.size(); ++i) {
				arr[i] = ordered[i].first;
			}
		}

		uint64_t getMortonKey2D(Vector2ui p) {
			uint64_t result = 0;

			for (int i = 0; i < K; i++) {
				result |= (p[0] & 1ULL << i) << i | (p[1] & 1ULL << i) << (i + 1);
			}
			return result;
		}

		uint64_t getMortonKey3D(Vector3ui p) {
			uint64_t result = 0;

			for (int i = 0; i < K; i++) {
				result |= (p[0] & 1ULL << i) << i | (p[1] & 1ULL << i) << (i + 1) | (p[2] & 1ULL << i) << (i + 2);
			}
			return result;
		}

		template <typename T, typename U>
		T normalize(const U &point, const U &pmin, const U &pmax) {
			auto origin = (point - pmin);
			auto size = (pmax - pmin);
			auto n = (origin / size) * NUM_CELL_ZCURVE3D;
			// floor
			return n.floor();
		}

	};
}