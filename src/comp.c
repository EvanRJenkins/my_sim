#include <math.h>   // For math
#include <stdlib.h> // For malloc/free
#include <stdio.h>
#include <stdint.h>
#include "imag.h"
#include "comp.h"
/*
Structs for circuits components
*/

/*
Functions for manipulating comp_t
*/

// Allocate memory for new Component struct
comp_t *COMP_New() {
    return (comp_t *) malloc(sizeof(comp_t));
}

// Initialize a component based on desired CompType
void COMP_InitVSOURCE(comp_t * target, float (*SourceFunction)(float)) {
    // Specify component type
    target->Type = VSOURCE;
    // Assign source function
    target->Value.SourceFunction = SourceFunction;
}
void COMP_InitISOURCE(E_CompType);
void COMP_InitRESISTOR(E_CompType);
void COMP_InitCAPACITOR(E_CompType);
void COMP_InitINDUCTOR(E_CompType);
