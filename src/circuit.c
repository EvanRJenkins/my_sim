#include <stdio.h>
#include "circuit.h"
// Array to track node labels in use
char NodeLabels[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '\0'};
#define MAX_NUM_NODES (sizeof(NodeLabels)/sizeof(NodeLabels[0])) - 1
uint8_t g_NodeLabelIndex = 0;
// Allocate memory for new node and initialize connections
Node_t *CIRCUIT_NewNode(Component_t *target1, 
                        Component_t *target2, Component_t *target3) {
    // Check if current node label is null terminator
    if (g_NodeLabelIndex < MAX_NUM_NODES) {
        Node_t *result = (Node_t *) malloc(sizeof(Node_t));
        result->Label = NodeLabels[g_NodeLabelIndex]; // Assign next label
        // Increment NodeLabelIndex
        ++g_NodeLabelIndex;
        // Assign targets if specified and not NULL
        if (target1 != NULL) {
            result->Connections[0] = target1;
        }
        if (target2 != NULL) {
            result->Connections[1] = target2;
        }
        if (target3 != NULL) {
            result->Connections[2] = target3;
        }
        return result;
    }
    else {
        printf("Node list full, terminating program\n");
        exit(EXIT_FAILURE);
        return NULL;
    }
}
