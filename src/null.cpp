#include "test.h"
#include "lcg.h"

static void normaldistf_null(float* data, size_t count) {
	LCG<float> r;
	for (size_t i = 0; i < count; i++)
		data[i] = r();
}

static void normaldist_null(double* data, size_t count) {
	LCG<double> r;
	for (size_t i = 0; i < count; i++)
		data[i] = r();
}

REGISTER_TEST(null);
