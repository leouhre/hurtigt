#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include "sinus.h"

#ifndef _MATH_H_
#define _MATH_H_

#define FIX14_SHIFT 14

#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b)  ( ((a) << FIX14_SHIFT) / b

typedef struct {
    int32_t x, y;
} vector_t;

void printFix(int32_t i);
int32_t expand(int32_t i);
int32_t calcsin(int32_t n);
int32_t calccos(int32_t n);
void rotateVector(vector_t *vec, int32_t v);

#endif /* _MATH_H_ */
