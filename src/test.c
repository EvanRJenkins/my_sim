#include "nodesolve.h"
#include "nodelut.h"
void PrintComponent(int index, Component_t *target) {
    printf("Index: %d\t", index);
    printf("Label: %s\t", target->Label);
    printf("+Node: %s\t", target->PosNode);
    printf("-Node: %s\n", target->NegNode);
}
/*
void PrintNode(int index, Node_t *target) {
    printf("Index: %d", index);
    printf("Label: %s", target->Label);
    printf("+Node: %s", target->);
    printf("-Node: %s\n", target->);
}
*/
int main(void) {
    MSNL_GetCircuitFromFile("test2.txt");
    printf("Found %d unique nodes...\n", g_NumNodesUnique);
    NODESOLVE_MapNodeConnections();
    printf("Successfully mapped node connections.\n");
    int i = 0;
    for (i = 0; i < g_NumLines; i++) {
        PrintComponent(i, &g_ComponentList[i]);
    }
    for (i = 0; i < g_NumNodesUnique; ++i) {
        NODESOLVE_PrintNodeConnections(&g_NodeList[i]);
    }
    // nodelut.c test
    NODELUT_MakeNodeTable();
    NODELUT_PrintNodeTable();
    // nodesolve.c test
    NODESOLVE_MakeBranchList();
    NODESOLVE_ComputeBranchImpedances();
    NODESOLVE_PrintAllBranchImpedances();
    NODESOLVE_PrintAllBranchNodes();
    NODESOLVE_MakeNodeMatrix(); 
    NODESOLVE_PopulateNodeMatrix();
    NODESOLVE_PrintNodeMatrix();
    // Free everything
    free(g_Lines);
    free(g_ComponentList);
    free(g_NodeList);
    free(g_BranchList);
    printf("Complete\n");
    return 0;
}

