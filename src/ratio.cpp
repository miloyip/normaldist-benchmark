#include "test.h"
#include "lcg.h"
#include <cassert>
#include <cmath>

/* Leva, Joseph L. "A fast normal random number generator."
 * ACM Transactions on Mathematical Software (TOMS) 18.4 (1992): 449-453. */

template <class T>
void ratio(T* data, size_t count) {
	LCG<T> r;
	T u, v, x, y, Q;
	constexpr T s = 0.449871;
	constexpr T t = -0.386595;
	constexpr T a = 0.19600;
	constexpr T b = 0.25472;
	constexpr T r1 = 0.27597;
	constexpr T r2 = 0.27846;
	constexpr T m = 1.715527769921414; /* 2*sqrt(2/e) */

	for (size_t i = 0; i < count; ++i) {
		do {
			u = 1 - r();
			v = (r() - (T)0.5) * m;
			x = u - s;
			y = std::fabs(v) - t;
			Q = x*x + y*(a*y - b*x);
		} while (Q >= r1 && (Q > r2 || v*v > -4*u*u * std::log(u));
		data[i] = v / u;
	}
}

static void normaldistf_ratio(float* data, size_t count) {
    ratio(data, count);
}

static void normaldist_ratio(double* data, size_t count) {
    ratio(data, count);
}

REGISTER_TEST(ratio);
