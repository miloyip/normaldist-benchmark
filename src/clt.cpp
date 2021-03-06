#include "test.h"
#include "lcg.h"
#include <cmath>

// By central limit theorem (CLT),
// U ~ [0, 1]
// S = sum U_i for i = 1 to M
// S ~ N(M / 2, M / 12)
// Z = (S - M / 2) / sqrt(M / 12)
// Z ~ N(0, 1)

template <class T, class RNG, int M>
static inline T clt(RNG& r) {
	static T inv = 1 / std::sqrt(T(M) / 12);

	T sum = r();
	for (int i = 1; i < M; i++)
		sum += r();

	return (sum - M / T(2)) * inv;
}

template <class T, int M>
static void clt(T* data, size_t count) {
	LCG<T> r;
	for (size_t i = 0; i < count; i++)
		data[i] = clt<T, LCG<T>, M>(r);
}

#define CLT_TEST(M)\
static void normaldistf_clt##M(float* data, size_t count) {\
    clt<float, M>(data, count);\
}\
static void normaldist_clt##M(double* data, size_t count) {\
    clt<double, M>(data, count);\
}\
REGISTER_TEST(clt##M)

CLT_TEST(4);
CLT_TEST(8);
CLT_TEST(16);
