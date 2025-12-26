#include "msnlparser.h"

int main(void) {
    MSNL_GetCircuitFromFile("test.txt");
    unsigned int i = 0;
    for (i = 0; i < g_LineIndex; i++) {
        printf("%s", g_Lines[i].Data);
    }
    printf("Line before MSNL_ParseLine\n");
    MSNL_ParseLine(g_Lines[0].Data);
    printf("Label: %s, Nominal Value: %f, Positive Node: %s, Negative Node: %s\n", g_ComponentList[0].Label, g_ComponentList[0].Value.Nominal, g_ComponentList[0].PosNode, g_ComponentList[0].NegNode);
    printf("Complete\n");
    return 0;
}

