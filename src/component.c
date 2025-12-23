#include <stdlib.h> // For malloc/free
#include "imaginarymath.h"
#include "component.h"
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
void COMP_InitISOURCE(comp_t * target, float (*SourceFunction)(float)) {
    // Specify component type
    target->Type = ISOURCE;
    // Assign source function
    target->Value.SourceFunction = SourceFunction;
}
void COMP_InitRESISTOR(comp_t * target, float resistance) {
    // Specify component type
    target->Type = RESISTOR;
    // Assign impedance
    target->Value.Z[0] = resistance;
    target->Value.Z[1] = 0.0f;
}
void COMP_InitCAPACITOR(comp_t * target, float capacitance) {
    // Specify component type
    target->Type = CAPACITOR;
    // Calculate and assign impedance
    float b = 1.0f / (ANGULAR_FREQUENCY * capacitance);
    target->Value.Z[0] = 0.0f;
    target->Value.Z[1] = b;
}
void COMP_InitINDUCTOR(comp_t * target, float inductance) {
    // Specify component type
    target->Type = INDUCTOR;
    // Calculate and assign impedance
    float b = ANGULAR_FREQUENCY * inductance;
    target->Value.Z[0] = 0.0f;
    target->Value.Z[1] = b;
}
