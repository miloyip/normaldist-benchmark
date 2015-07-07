#include "test.h"

#ifdef USE_SSE2

#include "lcg.h"
#include <cmath>

// By central limit theorem (CLT),
// U ~ [0, 1]
// S = sum U_i for i = 1 to M
// S ~ N(M / 2, M / 12)
// Z = (S - M / 2) / sqrt(M / 12)
// Z ~ N(0, 1)

template <int M>
static void clt_sse2(float* data, size_t count) {
	static const __m128 halfm = _mm_set1_ps(float(M) / 2);
	static const __m128 inv = _mm_set1_ps(1 / std::sqrt(float(M) / 12));

	LCG<__m128> r;
	for (size_t i = 0; i < count; i += 4) {
		__m128 sum = r();
		for (int j = 1; j < M; j++)
			sum = _mm_add_ps(sum, r());

		_mm_store_ps(&data[i], _mm_mul_ps(_mm_sub_ps(sum, halfm), inv));
	}
}

#define CLT_SSE2_TEST(M)\
static void normaldistf_clt##M##_sse2(float* data, size_t count) {\
    clt_sse2<M>(data, count);\
}\
REGISTER_TEST_FLOATONLY(clt##M##_sse2)

CLT_SSE2_TEST(4);
CLT_SSE2_TEST(8);
CLT_SSE2_TEST(16);

#endif