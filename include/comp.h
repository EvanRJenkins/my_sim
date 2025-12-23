#include <math.h>   // For math
#include <stdlib.h> // For malloc/free
#include <stdio.h>
#include <stdint.h>
#include "imag.h"
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
void COMP_InitISOURCE(E_CompType);
void COMP_InitRESISTOR(E_CompType);
void COMP_InitCAPACITOR(E_CompType);
void COMP_InitINDUCTOR(E_CompType);
