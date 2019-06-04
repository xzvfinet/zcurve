
#include "Header.h"
#include "Vector.h"
#include "Zcurve.h"

using namespace std;

typedef hj::Vector3f item;

int main() {
    hj::Zcurve zcurve;
    vector<item> arr;

    for (int i = 0; i <= 2; ++i)
        for (int j = 0; j <= 2; ++j)
            for (int k = 0; k <= 2; ++k) 
				arr.push_back(item(i, j, k));

    // WARNING! Exact boundary points (e.g. (0,0) or (5,5)) cause wrong ordering
    // so make sure that the range is larger than the actual values
    zcurve.order<float, 3>(hj::Vector3f(0), hj::Vector3f(2), arr, 20);

    for (auto el : arr) {
        cout << el;
    }

    return 0;
}