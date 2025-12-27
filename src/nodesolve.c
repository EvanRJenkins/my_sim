#include <math.h>
#include "nodesolve.h"
/*
The functions in this file are responsible for converting
the string format components from the msnl file parser into
a "circuit" that can be solved mathematically with nodal analysis.
*/
Branch_t *g_BranchList = NULL;
int g_BranchIndex = 0;
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
// STEP 2: CONVERT COMPONENTS TO BRANCHES
// Get memory
void NODESOLVE_MakeBranchList() {
    // Allocate memory for branch list, 1 per component at first
    g_BranchList = (Branch_t *) calloc(g_NumLines, sizeof(Branch_t));
    g_BranchIndex = 0;
}
// Convert passive components to impedances and populate g_BranchList
void NODESOLVE_ComputeBranchImpedances() {
    // For each component (line), calc impedance if passive
    int i = 0;
    printf("g_NumLines: %d", g_NumLines);
    debug();
    for (i = 0; i < g_NumLines; i++) {
        // Change calculation depending on type
        debug();
        strcpy(g_BranchList[i].Node1, g_ComponentList[i].PosNode);
        strcpy(g_BranchList[i].Node2, g_ComponentList[i].NegNode);
        switch (g_ComponentList[i].Type) {
            case ACTIVE:
                // Set source flag
                g_BranchList[g_BranchIndex].Behavior = SOURCE;
                break;
            case RESISTOR:
                // Z = R
                g_BranchList[g_BranchIndex].a = g_ComponentList[i].Value.Nominal;
                g_BranchList[g_BranchIndex].b = 0.0f;
                g_BranchList[g_BranchIndex].Behavior = NONE;
                // Increment index of branch list, doesn't track i
                g_BranchIndex++;
                break;
            case CAPACITOR:
                // Z = 1/jwC
                g_BranchList[g_BranchIndex].a = 0.0f;
                if ((g_ComponentList[i].Value.Nominal == 0) || (ANGULAR_FREQUENCY == 0)) {
                    g_BranchList[g_BranchIndex].b = 0.0f;
                    // Set status indicator
                    g_BranchList[g_BranchIndex].Behavior = INFINITE_Z;
                }
                else {
                    // Else, current is AC, do normal calculation
                    g_BranchList[g_BranchIndex].b = (1.0f / (ANGULAR_FREQUENCY * g_ComponentList[i].Value.Nominal));
                }
                g_BranchIndex++;
                break;
            case INDUCTOR:
                // Z = jwL
                g_BranchList[g_BranchIndex].a = 0.0f;
                if ((g_ComponentList[i].Value.Nominal == 0) || (ANGULAR_FREQUENCY == 0)) {
                    g_BranchList[g_BranchIndex].b = 0.0f;
                    // Set DC status indicator
                    g_BranchList[g_BranchIndex].Behavior = SHORT_CIRCUIT;
                }
                else {
                    // Else, current is AC, do normal calculation
                    g_BranchList[g_BranchIndex].b = (ANGULAR_FREQUENCY * g_ComponentList[i].Value.Nominal);
                }
                g_BranchIndex++;
                break;
            default:
                break;
        }
    }
}
// FOR TESTING: PRINT IMPEDANCE VALUES OF ALL BRANCHES
void NODESOLVE_PrintAllBranchImpedances() {
    int i = 0;
    printf("All branch impedances:\n");
    for (i = 0; i < g_NumLines; i++) {
        printf("\t%f %fj\n", g_BranchList[i].a, g_BranchList[i].b);
    }
}
// Populate node connections of each branch
void NODESOLVE_PrintAllBranchNodes() {
    int i = 0;
    printf("All branch nodes:\n");
    for (i = 0; i < g_NumLines; i++) {
        printf("\tBranch %d Node1: %s, Branch %d Node2: %s\n", i, g_BranchList[i].Node1, i, g_BranchList[i].Node2);
    }
}
