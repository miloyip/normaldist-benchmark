#include "test.h"

#ifdef USE_AVX

#include "lcg.h"
#include <cmath>

// By central limit theorem (CLT),
// U ~ [0, 1]
// S = sum U_i for i = 1 to M
// S ~ N(M / 2, M / 12)
// Z = (S - M / 2) / sqrt(M / 12)
// Z ~ N(0, 1)

template <int M>
static void clt_avx(float* data, size_t count) {
	static const __m256 halfm = _mm256_set1_ps(float(M) / 2);
	static const __m256 inv = _mm256_set1_ps(1 / std::sqrt(float(M) / 12));

	LCG<__m256> r;
	for (size_t i = 0; i < count; i += 4) {
		__m256 sum = r();
		for (int j = 1; j < M; j++)
			sum = _mm256_add_ps(sum, r());

		_mm256_store_ps(&data[i], _mm256_mul_ps(_mm256_sub_ps(sum, halfm), inv));
	}
}

#define CLT_AVX_TEST(M)\
static void normaldistf_clt##M##_avx(float* data, size_t count) {\
    clt_avx<M>(data, count);\
}\
REGISTER_TEST_FLOATONLY(clt##M##_avx)

CLT_AVX_TEST(4);
CLT_AVX_TEST(8);
CLT_AVX_TEST(16);

#endif