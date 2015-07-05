#include "test.h"
#include "lcg.h"
#include <cassert>

template <class T>
void boxmuller(T* data, size_t count) {
	assert(count % 2 == 0);
	static const T twopi = T(2.0 * 3.14159265358979323846);

	LCG r;
	for (size_t i = 0; i < count; i += 2) {
		T u1 = r();
		T u2 = r();
		T r = std::sqrt(-2 * std::log(u1));
		T theta = twopi * u2;
		data[i    ] = r * std::cos(theta);
		data[i + 1] = r * std::sin(theta);
	}
}

static void normaldistf_boxmuller(float* data, size_t count) {
    boxmuller(data, count);
}

static void normaldist_boxmuller(double* data, size_t count) {
    boxmuller(data, count);
}

REGISTER_TEST(boxmuller);
