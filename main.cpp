#include <stdint.h>
#include <cstdio>
#include <cmath>

typedef float (*unary_f) (float);
typedef double (*unary_d) (double);

struct unary {
    const char* name;
    unary_f f32;
    unary_d f64;
};

unary unaries[] = {
    {"floor", floorf, floor},
    {"round", roundf, round},
    {"ceil", ceilf, ceil},

    {"sqrt", sqrtf, sqrt},
    {"exp", expf, exp},
    {"log", logf, log},

    // Trigo
    {"cos", cosf, cos},
    {"acos", acosf, acos},

    {"sin", sinf, sin},
    {"asin", asinf, asin},

    {"tan", tanf, tan},
    {"atan", atanf, atan},
};

const int NUM_UNARIES = 12;

enum Mode {
    COUNT,
    CHECK_PROPERTY
};

union pun {
    float f;
    uint32_t i;
};

inline bool Equal(float a, float b) {
    return (a != a && b != b) // NaN
           || a == b;
}

int main() {
    static_assert(sizeof(float) == sizeof(uint32_t), "float should be the same size as uint32");

    Mode mode = COUNT;

    for (size_t i = 0; i < NUM_UNARIES; ++i) {
        const char* funcName = unaries[i].name;
        unary_f f32 = unaries[i].f32;
        unary_d f64 = unaries[i].f64;

        printf("Testing %s...\n", funcName);

        bool overflow = false;
        uint32_t numErrors = 0;

        pun p;
        p.i = 0;
        uint32_t old_i = p.i;

        float ff, ffdf;
        for (;;) {
            p.i += 1;

            if (p.i < old_i) {
                overflow = true;
                break;
            }
            old_i = p.i;

            float f = p.f;
            ff = f32(f);

            double df = static_cast<double>(f);
            double fdf = f64(df);
            ffdf = static_cast<float>(fdf);

            if (!Equal(ff, ffdf)) {
                if (mode == CHECK_PROPERTY) {
                    break;
                } else if (mode == COUNT) {
                    numErrors += 1;
                } else {
                    return 1;
                }
            }
        }

        if (mode == CHECK_PROPERTY) {
            printf("For %s: ", funcName);
            if (overflow)
                printf("No errors found");
            else {
                printf("Found an error for f=%.50f (aka %u as an uint32):\n", p.f, p.i);
                printf("\tf32=%.50f\n\tf64=%.50f", ff, ffdf);
            }
        } else if (mode == COUNT) {
            printf("For %s: %u errors found", funcName, numErrors);
        } else {
            return 2;
        }
        printf("\n");
    }
    return 0;
}
