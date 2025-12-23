#include <stdlib.h> // For malloc/free
#include <stdio.h>  // For error printing
#include "imaginarymath.h"
#include "component.h"

// Allocate memory for new Component struct
// Allocate memory for new Component and initialize
/*
To make a passive component, pass NULL, passive value,
and RESISTOR, CAPACITOR, or INDUCTOR.

To make an active component, pass the component function,
a float literal to passive_val, and ACTIVE.
*/
Component_t *COMP_New(float (*func_ptr)(void), float passive_val, 
                      E_CompType comp_type) {
    // Error if no active component function and active selected
    if ((func_ptr == NULL) && (comp_type == ACTIVE)) {
        printf("Error: Specified component type is active, but no function was provided. Program terminated.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }
    // Error if passive component specified but no value giver
    else if ((passive_val == 0.0f) && (comp_type != ACTIVE)) {
        printf("Error: Specified component type is passive, but no nominal value was provided. Program terminated.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }
    else {
        // Allocate space for new component
        Component_t *result = (Component_t *) malloc(sizeof(Component_t));
        result->Type = comp_type;
        switch (comp_type) {
            case ACTIVE:
                // Copy func_ptr to component's active function
                result->Value.ActiveFunction = func_ptr;
                break;
            case RESISTOR:
                // passive_val goes to a (real_part)
                result->Value.Z[0] = passive_val;
                result->Value.Z[1] = 0.0f;
                break;
            case CAPACITOR:
                // passive_val goes to imaginary part (1/jwC)
                result->Value.Z[0] = 0.0f;
                if (ANGULAR_FREQUENCY == 0.0f) {
                    result->Value.Z[1] = 0.0f;   
                }
                else {
                    result->Value.Z[1] = (float) (1.0f / (ANGULAR_FREQUENCY * passive_val));
                }
                break;
            case INDUCTOR:
                result->Value.Z[0] = 0.0f;
                result->Value.Z[1] = (float) (ANGULAR_FREQUENCY * passive_val);
                break;
            default:
                printf("Error: Default case reached. Program terminated.\n");
                exit(EXIT_FAILURE);
                return NULL;
                break;
        }
    // Return initialized component struct pointer 
    return result;
    }
}

