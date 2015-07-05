#include "test.h"
#include "lcg.h"
#include <cassert>
#include <algorithm>

// http://home.online.no/~pjacklam/notes/invnorm/
template <class T>
static T normsinv(T p) {
    static const T a1 = T(-3.969683028665376e+01);
    static const T a2 = T( 2.209460984245205e+02);
    static const T a3 = T(-2.759285104469687e+02);
    static const T a4 = T( 1.383577518672690e+02);
    static const T a5 = T(-3.066479806614716e+01);
    static const T a6 = T( 2.506628277459239e+00);
    static const T b1 = T(-5.447609879822406e+01);
    static const T b2 = T( 1.615858368580409e+02);
    static const T b3 = T(-1.556989798598866e+02);
    static const T b4 = T( 6.680131188771972e+01);
    static const T b5 = T(-1.328068155288572e+01);
    static const T c1 = T(-7.784894002430293e-03);
    static const T c2 = T(-3.223964580411365e-01);
    static const T c3 = T(-2.400758277161838e+00);
    static const T c4 = T(-2.549732539343734e+00);
    static const T c5 = T( 4.374664141464968e+00);
    static const T c6 = T( 2.938163982698783e+00);
    static const T d1 = T( 7.784695709041462e-03);
    static const T d2 = T( 3.224671290700398e-01);
    static const T d3 = T( 2.445134137142996e+00);
    static const T d4 = T( 3.754408661907416e+00);

    T q = std::min(p, 1 - p), u;
    if (q > 0.02425) {
        // Central region
        T d = q - T(0.5);
        T t = d * d;
        u = d * (((((a1 * t + a2) * t + a3) * t + a4) * t + a5) * t + a6) /
                (((((b1 * t + b2) * t + b3) * t + b4) * t + b5) * t + 1);
    }
    else {
        // Tail region
        T t = std::sqrt(-2 * std::log(q));
        u = (((((c1 * t + c2) * t + c3) * t + c4) * t + c5) * t + c6) / 
            ((((d1 * t + d2) * t + d3) * t + d4) * t + 1);
    }
    
    return p > 0.5 ? -u : u;
}

template <class T>
static void inverse(T* data, size_t count) {
	LCG r;
	for (size_t i = 0; i < count; i++)
        data[i] = normsinv(r());
}

static void normaldistf_inverse(float* data, size_t count) {
    inverse(data, count);
}

static void normaldist_inverse(double* data, size_t count) {
    inverse(data, count);
}

REGISTER_TEST(inverse);
