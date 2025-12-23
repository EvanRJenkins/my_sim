/*
This file provides circuit structure elements such as wires and ground
*/
#include <stdlib.h>
#include "component.h"
// Wire type
// Holds pointers to connected components
typedef struct Node {
    char Label;
    Component_t *Connections[3];  // Expand this with malloc/realloc later!
} Node_t;
// Allocate memory for new node and initialize connections
Node_t *CIRCUIT_NewNode(Component_t *target1, 
                        Component_t *target2, Component_t *target3);
