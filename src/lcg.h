#pragma once

#include <cstdint>

template <class T>
class LCG;

template <>
class LCG<float> {
public:
    LCG() : x(1) {}

    float operator()() {
        x = x * 1664525 + 1013904223; // Numerical Recipes
        union {
            uint32_t u;
            float f;
        }u;
        u.u = (x >> 9) | 0x3F800000;
        return u.f - 1.0f;
    }

private:
    uint32_t x;
};

template <>
class LCG<double> {
public:
    LCG() : x(1) {}

    float operator()() {
        x = x * 2862933555777941757 + 3037000493; // http://nuclear.llnl.gov/CNP/rng/rngman/node4.html
        union {
            uint64_t u;
            double f;
        }u;
        u.u = (x >> 12) | (uint64_t(0x3FF00000) << 32);
        return u.f - 1.0f;
    }

private:
    uint64_t x;
};
