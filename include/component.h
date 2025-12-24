#include <stdlib.h> // For malloc/free
#include "imaginarymath.h"
// For functions to work if not defined
#ifndef ANGULAR_FREQUENCY
    #define ANGULAR_FREQUENCY 1.0f
#endif
#define MAX_NUM_PARAMS 2
/*
Structs for circuits components
*/
typedef enum { 
    ACTIVE,
    RESISTOR, 
    CAPACITOR, 
    INDUCTOR
} E_CompType;
// For holding active function information
typedef struct ActiveFunctionInfo {
    float (*ptr)(float, float *);
    char Params[MAX_NUM_PARAMS + 1];
    unsigned char ParamsCount;
} ActiveFunction;

// For changing component value with type
union TypeValue {
    ActiveFunction ActiveFunction;
    float Nominal;
};

typedef struct Component {
    char Label[5];
    // Component type
    E_CompType Type;
    // Varying value
    union TypeValue Value;
} Component_t;

/*
Functions for manipulating Component_t
*/

// Allocate memory for new Component and initialize
/*
To make a passive component, pass NULL, passive value,
and RESISTOR, CAPACITOR, or INDUCTOR.

To make an active component, pass the component function,
a float literal to passive_val, and ACTIVE.
*/
Component_t *COMP_New(const char *label, float (*func_ptr)(void), 
                        float passive_val, E_CompType comp_type);

