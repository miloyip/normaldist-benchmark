#include "test.h"

#ifdef USE_AVX

#include "lcg.h"
#include <cassert>
#include <cmath>

static void normaldistf_boxmuller_avx(float* data, size_t count) {
	assert(count % 16 == 0);
	const __m256 twopi = _mm256_set1_ps(2.0f * 3.14159265358979323846f);
	const __m256 one = _mm256_set1_ps(1.0f);
	const __m256 minustwo = _mm256_set1_ps(-2.0f);

	LCG<__m256> r;
	for (size_t i = 0; i < count; i += 16) {
        __m256 u1 = _mm256_sub_ps(one, r()); // [0, 1) -> (0, 1]
        __m256 u2 = r();
		__m256 radius = _mm256_sqrt_ps(_mm256_mul_ps(minustwo, log256_ps(u1)));
		__m256 theta = _mm256_mul_ps(twopi, u2);
        __m256 sintheta, costheta;
        sincos256_ps(theta, &sintheta, &costheta);
		_mm256_store_ps(&data[i    ], _mm256_mul_ps(radius, costheta));
		_mm256_store_ps(&data[i + 8], _mm256_mul_ps(radius, sintheta));
	}
}

REGISTER_TEST_FLOATONLY(boxmuller_avx);

#endif // USE_AVX
