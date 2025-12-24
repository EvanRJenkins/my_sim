#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <stdio.h>
#include <math.h>

typedef float (*ActiveFunc_t)(float t, float args[]);

// Declared here so the table can reference
float func_SIN(float t, float args[]);
float func_SQUARE(float t, float args[]);
float func_PULSE(float t, float args[]);
float func_DC(float t, float args[]);

// 3. Define the Mapping Structure
typedef struct {
    char Name[16];          // String found in the .msnl file
    ActiveFunc_t FuncPtr;   // C function to call
} FunctionMapping_t;

//Global Function Table
// Maps the text string to the function pointer.
extern FunctionMapping_t g_FunctionTable[];

#endif
