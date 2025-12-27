#ifndef FUNCTIONLUT_H
#define FUNCTIONLUT_H

#include <stdlib.h> // For NULL
#include <math.h>
#include "circuit.h" // For size macros

typedef float (*ActiveFunc_t)(float t, float args[]);

// Declared here so the table can reference
float func_SIN(float t, float args[]);
float func_SQUARE(float t, float args[]);
float func_PULSE(float t, float args[]);
float func_DC(float t, float args[]);

// LUT mapping struct
typedef struct {
    char Name[MAX_LABEL_LENGTH + 1]; // String found in the .msnl file
    ActiveFunc_t FuncPtr;   // C function to call
} FunctionMap_t;

//Global Function Table
// Maps the text string to the function pointer.
extern FunctionMap_t g_FunctionTable[];

#endif
