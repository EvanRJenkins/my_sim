#include "msnlparser.h"

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
    int i = 0;
    for (i = 0; i < g_NumLines; i++) {
        PrintComponent(i, &g_ComponentList[i]);
    }
    printf("%d\n", g_NumNodesUnique);
    free(g_ComponentList);
    free(g_NodeList);
    free(g_Lines);
    printf("Complete\n");
    return 0;
}

