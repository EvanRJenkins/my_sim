#include <math.h>
#include "nodesolve.h"
/*
The functions in this file are responsible for converting
the string format components from the msnl file parser into
a "circuit" that can be solved mathematically with nodal analysis.
*/
// STEP 1: IDENTIFY NODES
void NODESOLVE_MapNodeConnections() {
    int i = 0;
    int j = 0;
    // Iterate through g_NodeList and map connection ptrs for each node
    for (i = 0; i < g_NumNodesUnique; i++) {
        // i is the index for tracking current Node_t
        // j is the index for tracking current Component_t
        for (j = 0; j < g_NumLines; j++) {
            // Check if Comp j is connected to Node i
            if (!strncmp(g_ComponentList[j].PosNode, g_NodeList[i].Label, MAX_LABEL_LENGTH)) {
                // Map a connection ptr to that component
                g_NodeList[i].Connections[g_NodeList[i].NumConnections] = &g_ComponentList[j];
                g_NodeList[i].NumConnections++;
            }
            // Do the same with negative
            if (!strncmp(g_ComponentList[j].NegNode, g_NodeList[i].Label, MAX_LABEL_LENGTH)) {
                // Map a connection ptr to that component
                g_NodeList[i].Connections[g_NodeList[i].NumConnections] = &g_ComponentList[j];
                g_NodeList[i].NumConnections++;
            }
        }
    }
}
// FOR TESTING: PRINT LABELS OF CONNECTED COMPONENTS AT A NODE
void NODESOLVE_PrintNodeConnections(Node_t * target) {
    int i = 0;
    printf("Components connected to Node %s:\n", target->Label);
    for (i = 0; i < g_NodeList[i].NumConnections; i++) {
        printf("\t%s\n", target->Connections[i]->Label);
    }
}
