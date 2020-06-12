#include "math.h"

void printFix(int32_t i) {
    // Prints a signed 16.16 fixed point number
    if ((i & 0x80000000) != 0) {
    // Handle negative numbers
        printf("-");
        i = ~i + 1;
    }
    printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
    // Print a maximum of 4 decimal digits to avoid overflow
}

int32_t expand(int32_t i) {
    // Converts an 18.14 fixed point number to 16.16
    return i << 2;
}

int32_t calcsin(int32_t n) {
    if (n < 0) n += 512 * (n / 512 + 1);
    n %= 512;
    return SIN[n];
}

int32_t calccos(int32_t n) {
    return calcsin(n + (int32_t) 128);
}

void rotateVector(vector_t *vec, int32_t v) {
    int32_t tempx;
    tempx = FIX14_MULT(vec->x << 14, calccos(v)) - FIX14_MULT(vec->y << 14, calcsin(v));
    vec->y = FIX14_MULT(vec->x << 14, calcsin(v)) + FIX14_MULT(vec->y << 14, calccos(v));
    vec->x = tempx;
}
