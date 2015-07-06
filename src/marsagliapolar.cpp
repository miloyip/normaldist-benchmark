#include "test.h"
#include "lcg.h"
#include <cassert>
#include <cmath>

template <class T>
void marsagliapolar(T* data, size_t count) {
	assert(count % 2 == 0);

	LCG<T> r;
	for (size_t i = 0; i < count; i += 2) {
		T u, v, s;
		do {
			u = r() * 2 - 1;
			v = r() * 2 - 1;
			s = u * u + v * v;
		} while (s >= 1 || s == 0);

		T mul = std::sqrt(-2 * std::log(s) / s);
		data[i    ] = mul * u;
		data[i + 1] = mul * v;
	}
}

static void normaldistf_marsagliapolar(float* data, size_t count) {
    marsagliapolar(data, count);
}

static void normaldist_marsagliapolar(double* data, size_t count) {
    marsagliapolar(data, count);
}

REGISTER_TEST(marsagliapolar);
