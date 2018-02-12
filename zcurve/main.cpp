
#include "Header.h"
#include "Vector.h"
#include "Zcurve.h"

using namespace std;

typedef Vector3f item;

inline float myrand() {
	return float(rand()) / RAND_MAX;
}

int main() {

	auto zcurve = make_unique<Zcurve>(Vector3f(0,0,0), Vector3f(100,100,100));
	vector<item> arr;

	const int NUM = 100;
	for (int i = 0; i < NUM; ++i) {
		item a(myrand(), myrand(), myrand());
		arr.push_back(a);
	}

	zcurve->order3D(arr, 20);

	for (auto el : arr) {
		cout << el[0] << " " << el[1] << " " << el[2] << endl;
	}

	system("pause");
	return 0;
}