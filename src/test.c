#include "msnlparser.h"

int main(void) {
    MSNL_GetCircuitFromFile("test.txt");
    int i = 0;
    for (i = 0; i < g_NumLines; i++) {
        printf("%s", g_Lines[i].Data);
    }
    printf("Line before MSNL_ParseLine\n");
    int j = 0;
    for (j = 0; j < g_NumLines; j++) {
        MSNL_ParseLine(g_Lines[j].Data);
        printf("Comp j Label: %s \n", g_ComponentList[j].Label);
    }
    free(g_ComponentList);
    free(g_NodeList);
    free(g_Lines);
    printf("Complete\n");
    return 0;
}

