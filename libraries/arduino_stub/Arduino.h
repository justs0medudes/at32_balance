#pragma once

#include <cstdint>
#include <cstddef>
#include "at32f403a_407_def.h"

// basic types
typedef uint8_t byte;

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

// constrain
#define constrain(x, a, b) ((x)<(a)?(a):((x)>(b)?(b):(x)))

// timing
extern unsigned long _micros();
extern "C" uint32_t micros(void);

#define delayMicroseconds(x) delay_us(x)

// dummy Print class
class Print {
public:
    virtual size_t write(uint8_t b) {
        UNUSED(b);
        return 1;
    }

    static void print(const char* s) { UNUSED(s); }
    static void print(float f) { UNUSED(f); }
    static void print(int i) { UNUSED(i); }

    static void println(const char* s) { UNUSED(s); }
    static void println(float f) { UNUSED(f); }
    static void println(int i) { UNUSED(i); }

    static void print(float f, int d) { UNUSED(f); UNUSED(d); }
    static void print(int i, int b) { UNUSED(i); UNUSED(b); }
};

class SPIClass {
public:
    static void begin() {}

    static uint8_t transfer(uint8_t data) {
        return data;  // fine
    }
};
