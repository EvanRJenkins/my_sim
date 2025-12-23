#include <stdlib.h> // For malloc/free
#include "imaginarymath.h"
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
} Component_t;

/*
Functions for manipulating Component_t
*/

// Allocate memory for new Component struct
Component_t *COMP_New();

// Initialize a component based on desired CompType
void COMP_InitVSOURCE(Component_t * target, float (*SourceFunction)(float));
void COMP_InitISOURCE(Component_t * target, float (*SourceFunction)(float));
void COMP_InitRESISTOR(Component_t * target, float resistance);
void COMP_InitCAPACITOR(Component_t * target, float capacitance);
void COMP_InitINDUCTOR(Component_t * target, float inductance);
