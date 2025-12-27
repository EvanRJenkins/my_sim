#ifndef CIRCUIT_H
#define CIRCUIT_H
/*
This file provides circuit structure elements such as wires and ground
*/
#include <stdlib.h>
#include <stdint.h>
// For functions to work if not defined
#ifndef ANGULAR_FREQUENCY
    #define ANGULAR_FREQUENCY 1.0f
#endif
#define MAX_NUM_PARAMS 6
#define MAX_LABEL_LENGTH 10
#define MAX_NUM_CONNECTIONS 10
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
    int ParamsCount;
} ActiveFunction;

// For changing component value with type
union TypeValue {
    ActiveFunction ActiveFunction;
    float Nominal;
};

typedef struct Component {
    char Label[MAX_LABEL_LENGTH];
    // Component type
    E_CompType Type;
    // Varying value
    union TypeValue Value;
    // Connected nodes
    char PosNode[MAX_LABEL_LENGTH + 1];
    char NegNode[MAX_LABEL_LENGTH + 1];
} Component_t;

// Holds pointers to connected components
typedef struct Node {
    char Label[MAX_LABEL_LENGTH + 1];
    Component_t *Connections[MAX_NUM_CONNECTIONS];  // Expand this with malloc/realloc later!
    int NumConnections;
} Node_t;
#endif // Header define
