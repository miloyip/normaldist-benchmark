#pragma once

class LCG {
public:
    LCG() : x(1) {}

    float operator()() {
        x = x * 1664525 + 1013904223; // Numerical Recipes
        union {
            unsigned u;
            float f;
        }u;
        u.u = (x >> 9) | 0x3F800000;
        return u.f - 1.0f;
    }

private:
    unsigned x;
};
