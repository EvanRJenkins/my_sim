#include "imag.h"
#include <math.h>     // For math
#include <stdio.h>    // For print
#include <stdlib.h>   // For malloc/free
#include <stdint.h>
// Create array for new imag_t
float *IMAG_New() {
    // Allocate 2 element array
    float *new_imag = (float*) malloc(2 * sizeof(float));
    // Return array name ptr
    return new_imag;
}
// Initialize coefficients of target complex number
void IMAG_Init(float * target, float a, float b) {
    target[0] = a;
    target[1] = b;
}

// Return complex conjugate of imag_t
float *IMAG_Conjugate(float * target) {
    float new_a = target[0];
    float new_b = -target[1];
    float *result = IMAG_New();
    IMAG_Init(result, new_a, new_b);
    return result;
}

// Add two complex numbers and return result
float *IMAG_Add(float * target1, float * target2) {
    float new_a = target1[0] + target2[0];
    float new_b = target1[1] + target2[1];
    float *result = IMAG_New();
    IMAG_Init(result, new_a, new_b);
    return result;
}

// Subtract two complex numbers and return result
float *IMAG_Sub(float * target1, float * target2) {
    float new_a = target1[0] - target2[0];
    float new_b = target1[1] - target2[1];
    float *result = IMAG_New();
    IMAG_Init(result, new_a, new_b);
    return result;
}

// Multiply two complex numbers and return result
float *IMAG_Mult(float * target1, float * target2) {
    // Real * real + -(imag * imag) because j * j = -1
    float new_a = (target1[0] * target2[0]) - (target1[1] * target2[1]);
    float new_b = (target1[1] * target2[0]) + (target1[0] * target2[1]);
    float *result = IMAG_New();
    IMAG_Init(result, new_a, new_b);
    return result;
}

// Divide two complex numbers and return result
float *IMAG_Div(float * target1, float * target2) {
    // Multply numerator and denom by denom conjugate
    float *conjugate = IMAG_Conjugate(target2);
    // Numerator * Denominator complex conjugate
    float *numerator = IMAG_Mult(target1, conjugate);
    free(conjugate);
    // Denominator is a^2 + b^2
    float denominator = target2[0]*target2[0] + target2[1]*target2[1];
    numerator[0] /= denominator;
    numerator[1] /= denominator;
    return numerator;
}
