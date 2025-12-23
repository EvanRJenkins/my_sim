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
    ACTIVE,
    RESISTOR, 
    CAPACITOR, 
    INDUCTOR
} E_CompType;
// For changing component value with type
union TypeValue {
    // Source unction pointer
    float (*ActiveFunction)(void);
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

// Allocate memory for new Component and initialize
/*
To make a passive component, pass NULL, passive value,
and RESISTOR, CAPACITOR, or INDUCTOR.

To make an active component, pass the component function,
a float literal to passive_val, and ACTIVE.
*/
Component_t *COMP_New(float (*func_ptr)(void), float passive_val, 
                      E_CompType comp_type);

