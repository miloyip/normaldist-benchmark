#include "test.h"

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER > 1700) // VS2012

#include <random>

template <class RealType>
static void genericNormalDist(RealType* data, size_t count) {
	std::minstd_rand gen;
	std::normal_distribution<RealType> d;
	for (size_t i = 0; i < count; i++)
		data[i] = d(gen);
}

static void normaldistf_cpp11random(float* data, size_t count) {
	genericNormalDist(data, count);
}

static void normaldist_cpp11random(double* data, size_t count) {
	genericNormalDist(data, count);
}

REGISTER_TEST(cpp11random);

#endif
