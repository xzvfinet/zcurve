#pragma once

#include "Header.h"
#include "Vector.h"

namespace hj {
	template<typename Type>
	int bits_of_type =
		(std::is_same<Type, uint8_t>::value) ? 8 :
		(std::is_same<Type, uint16_t>::value) ? 16 :
		(std::is_same<Type, uint32_t>::value) ? 32 :
		(std::is_same<Type, uint64_t>::value) ? 64 :
		(std::is_same<Type, uint128_t>::value) ? 128 : 0;

	template <int Dimension, typename DataType, typename UnsignedIntegerType = uint64_t>
	class Zcurve {
		static_assert(Dimension > 0, "Parameter 'Dimension' must be > 0.");
		static_assert(std::is_constructible<UnsignedIntegerType, DataType>::value,
			"UnsignedIntegerType instance cannot be constructed using DataType.");

		using _Vector = Vector<DataType, Dimension>;

		const float eps = 1e-6f;
		const UnsignedIntegerType maxCells = UnsignedIntegerType(1) << (bits_of_type<UnsignedIntegerType> / Dimension);

	public:
		Zcurve() {
		}

		// For arbtrary type of element with accessor
		template <typename ArrayElementType>
		void order(
			const _Vector&										pmin,
			const _Vector&										pmax,
			std::vector<ArrayElementType>&						arr,
			const std::function<_Vector&(ArrayElementType&)>&	accessor = 0,
			const std::function<void(void)>&					progressUpdate = 0)
		{
			std::vector<std::pair<_Vector, UnsignedIntegerType>> ordered(
				arr.size());

			for (size_t i = 0; i < arr.size(); ++i) {
				_Vector& v = accessor(arr[i]);
				auto p = normalize(v, pmin - eps, pmax + eps);
				UnsignedIntegerType key = getMortonKey(p);
				ordered[i] = std::make_pair(v, key);
			}

			std::sort(ordered.begin(), ordered.end(),
				[&progressUpdate](
					std::pair<_Vector, UnsignedIntegerType>& lhs,
					std::pair<_Vector, UnsignedIntegerType>& rhs) {
				if (progressUpdate) progressUpdate();
				return lhs.second < rhs.second;
			});

			for (auto i = 0u; i < arr.size(); ++i) {
				accessor(arr[i]) = ordered[i].first;
			}
		}

		// Specialization for hj::Vector
		template <>
		void order<_Vector>(
			const _Vector&								pmin,
			const _Vector&								pmax,
			std::vector<_Vector>&						arr,
			const std::function<_Vector&(_Vector&)>&	accessor,
			const std::function<void(void)>&			progressUpdate)
		{
			std::vector<std::pair<_Vector, UnsignedIntegerType>> ordered(
				arr.size());

			for (size_t i = 0; i < arr.size(); ++i) {
				_Vector& v = arr[i];
				auto p = normalize(v, pmin - eps, pmax + eps);
				UnsignedIntegerType key = getMortonKey(p);
				ordered[i] = std::make_pair(v, key);
			}

			std::sort(ordered.begin(), ordered.end(),
				[&progressUpdate](
					std::pair<_Vector, UnsignedIntegerType>& lhs,
					std::pair<_Vector, UnsignedIntegerType>& rhs) {
				if (progressUpdate) progressUpdate();
				return lhs.second < rhs.second;
			});

			for (auto i = 0u; i < arr.size(); ++i) {
				arr[i] = ordered[i].first;
			}
		}

		UnsignedIntegerType getMortonKey(const _Vector& p, const _Vector& pMin, const _Vector& pMax) {
			return getMortonKey(normalize(p, pMin - eps, pMax + eps));
		}
		UnsignedIntegerType getMortonKey(const _Vector& _p) {
			UnsignedIntegerType result = 0;

			_Vector normalized(_p);
			normalized *= maxCells;

			auto n = normalized.floor<UnsignedIntegerType>();

			for (int i = 0; i < bits_of_type<UnsignedIntegerType>; i++) {
				for (int j = 0; j < Dimension; ++j) {
					result = result | ((n[j] & UnsignedIntegerType(1) << i) << (i + j));
				}
			}

			return result;
		}
		inline static _Vector normalize(const _Vector& point,
			const _Vector& pmin,
			const _Vector& pmax) {
			auto origin = (point - pmin);
			auto size = (pmax - pmin);

			// [0,0] ~ [1,1]
			return (origin / size);
		}
	};

}  // namespace hj