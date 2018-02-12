#pragma once

#include "Header.h"
#include "Vector.h"

#define NUM_CELL_ZCURVE3D 1048576
#define NUM_CELL_ZCURVE5D 4096
#define NUM_CELL_ZCURVE6D 1024
#define NUM_CELL_ZCURVE8D 8

class Zcurve
{
public:
	Zcurve(Vector3f min, Vector3f max) : bound{ min, max } {}

	void order3D(std::vector<Vector3f>& arr, int bits) {
		this->K = bits;

		std::vector<std::pair<Vector3f, uint64_t>> ordered(arr.size());
		for (auto i = 0u; i < arr.size(); ++i) {
			auto p = normalize(arr[i]);
			uint64_t key = mortonKey(p);
			ordered[i] = std::make_pair(arr[i], key);
		}

		std::sort(ordered.begin(), ordered.end(), [](auto lhs, auto rhs) {
			return lhs.second < rhs.second;
		});

		for (auto i = 0u; i < arr.size(); ++i) {
			arr[i] = ordered[i].first;
		}
	}

private:
	int K;
	// 0: min, 1: max
	Vector3f bound[2];

	uint64_t mortonKey(Vector3ui p) {
		uint64_t result = 0;

		for (int i = 0; i < K; i++) {
			result |= (p[0] & 1ULL << i) << i | (p[1] & 1ULL << i) << (i + 1) | (p[2] & 1ULL << i) << (i + 2);
		}

		return result;
	}

	Vector3ui normalize(Vector3f point) {
		auto min = (point - bound[0]);
		auto size = (bound[1] - bound[0]);
		auto n = (min / size) * NUM_CELL_ZCURVE3D;
		// floor
		return Vector3ui(uint64_t(n[0]), uint64_t(n[1]), uint64_t(n[2]));
	}

};

