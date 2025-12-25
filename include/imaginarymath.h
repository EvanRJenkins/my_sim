#ifndef IMAGINARYMATH_H
#define IMAGINARYMATH_H
/*
Complex number type definition and math functions
*/
#include <stdlib.h> // For malloc/free
#include <stdint.h>
#define REAL(x) x[0]
#define IMAG(x) x[1]


// Allocate a new imaginary number array[2]
float *IMAG_New();

// Initialize values of an imaginary number
void IMAG_Init(float * target, float a, float b);

// Return complex conjugate of target
float *IMAG_Conjugate(float * target);

// Add two complex numbers and return result
float *IMAG_Add(float * target1, float * target2);

// Subtract two complex numbers and return result
float *IMAG_Sub(float * target1, float * target2);

// Multiply two complex numbers and return result
float *IMAG_Mult(float * target1, float * target2);

// Divide two complex numbers and return result
float *IMAG_Div(float * target1, float * target2);

#endif // Header define
