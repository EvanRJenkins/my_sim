#include <math.h>   // For math
#include <stdlib.h> // For malloc/free
#include <stdio.h>
#include <stdint.h>
#include "imag.h"
// For functions to work if not defined
#ifndef ANGULAR_FREQUENCY
    #define ANGULAR_FREQUENCY 1.0f
#endif
/*
Structs for circuits components
*/
typedef enum {
    VSOURCE, 
    ISOURCE, 
    RESISTOR, 
    CAPACITOR, 
    INDUCTOR
} E_CompType;
// For changing component value with type
union TypeValue {
    // Source unction pointer
    float (*SourceFunction)(float);
    // Impedance
    float Z[2];
};

typedef struct Component {
    // Component type
    E_CompType Type;
    // Varying value
    union TypeValue Value;
} comp_t;

/*
Functions for manipulating comp_t
*/

// Allocate memory for new Component struct
comp_t *COMP_New();

// Initialize a component based on desired CompType
void COMP_InitVSOURCE(comp_t * target, float (*SourceFunction)(float));
void COMP_InitISOURCE(comp_t * target, float (*SourceFunction)(float));
void COMP_InitRESISTOR(comp_t * target, float resistance);
void COMP_InitCAPACITOR(comp_t * target, float capacitance);
void COMP_InitINDUCTOR(comp_t * target, float inductance);
