#include <iostream>
#include <random>
#include <chrono>

#include "Header.h"
#include "Vector.h"
#include "Zcurve.h"

using namespace std;

const int DIM = 3;
const float eps = 1e-6;
using item = hj::Vector<float, DIM>;
using hclock = chrono::high_resolution_clock;
using duration = chrono::duration<double>;

template <size_t n>
std::array<float, n> create_random_data() {
	std::random_device r;
	std::seed_seq      seed{ r(), r(), r(), r(), r(), r(), r(), r() };
	std::mt19937       eng(seed); // a source of random data

	std::uniform_real_distribution<float> dist;
	std::array<float, n> v;

	generate(begin(v), end(v), bind(dist, eng));
	return v;
}

int main() {

	/*for (size_t i = 0; i < 10; ++i)
		arr.push_back(create_random_data<DIM>());
		*/

	int a = 1;

	///////////////////////////////////////////////////////////////
	/* TEST1. Just ordering **************************************/
	///////////////////////////////////////////////////////////////
	hj::Zcurve<DIM, float> zcurve;
	vector<pair<int, item>> arr;
	int idx = 0;
	arr.push_back({ idx++, { .5f, .5f, .5f } });
	arr.push_back({ idx++, { 0.f, .5f, 0.f } });
	arr.push_back({ idx++, { 0.f, .5f, .5f } });
	arr.push_back({ idx++, { .5f, .5f, 0.f } });
	arr.push_back({ idx++, { 0.f, 0.f, 0.f } });
	arr.push_back({ idx++, { .5f, 0.f, .5f } });
	arr.push_back({ idx++, { 0.f, 0.f, .5f } });
	for (size_t i = 0; i < 10000; ++i)
		arr.push_back({ idx++, create_random_data<DIM>() });
	/*
	After ordering:
	0, [0, 0, 0]
	1, [0, 0.5, 0]
	2, [0.5, 0.5, 0]
	3, [0, 0, 0.5]
	4, [0.5, 0, 0.5]
	5, [0, 0.5, 0.5]
	6, [0.5, 0.5, 0.5]
	*/

	/*cout << "\nBefore ordering: \n";
	for (auto el : arr) {
		cout << el.first << ", " << el.second;
	}*/

	// WARNING! Exact boundary points (e.g. (0,0) or (5,5)) cause wrong ordering
	// so make sure that the range is larger than the actual values
	auto start = hclock::now();
	zcurve.order<pair<int, item>>(item(0.f) - eps, item(1.f) + eps, arr,
		[](auto& el) -> item& {
		return el.second;
	});
	duration time = hclock::now() - start;
	/*cout << "\nAfter ordering: \n";
	for (auto el : arr) {
		cout << el.second;
	}*/
	std::cout << "\ntook " << time.count() << "s to make mortonkey and sort" << std::endl;

	///////////////////////////////////////////////////////////////
	/* TEST2. Just ordering **************************************/
	///////////////////////////////////////////////////////////////
	hj::Zcurve<DIM, float> zcurve2;
	vector<item> arr2;
	idx = 0;
	arr2.push_back({ .5f, .5f, .5f });
	arr2.push_back({ 0.f, .5f, 0.f });
	arr2.push_back({ 0.f, .5f, .5f });
	arr2.push_back({ .5f, .5f, 0.f });
	arr2.push_back({ 0.f, 0.f, 0.f });
	arr2.push_back({ .5f, 0.f, .5f });
	for (size_t i = 0; i < 10000; ++i)
		arr2.push_back(create_random_data<DIM>());

	start = hclock::now();
	zcurve2.order(item(0.f) - eps, item(1.f) + eps, arr2);
	time = hclock::now() - start;
	/*cout << "\nAfter ordering: \n";
	for (auto el : arr2) {
		cout << el;
	}*/
	std::cout << "\ntook " << time.count() << "s to make mortonkey and sort" << std::endl;


	return 0;
}