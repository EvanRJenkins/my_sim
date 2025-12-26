#include "msnlparser.h"

int main(void) {
    MSNL_GetCircuitFromFile("test.txt");
    unsigned int i = 0;
    for (i = 0; i < g_NumLines; i++) {
        printf("%s", g_Lines[i].Data);
    }
    printf("Line before MSNL_ParseLine\n");
    unsigned int j = 1;
    MSNL_ParseLine(g_Lines[j].Data);
    printf("Comp 1 NegNode Label: %s Comp 2 Comp Label: %s\n", g_ComponentList[j-1].NegNode, g_ComponentList[j].Label);
    printf("Complete\n");
    return 0;
}

