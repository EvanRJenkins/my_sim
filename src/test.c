#include "msnlparser.h"

int main(void) {
    MSNL_GetCircuitFromFile("test.txt");
    int i = 0;
    for (i = 0; i < g_NumLines; i++) {
        printf("%s", g_Lines[i].Data);
    }
    for (i = 0; i < g_NumLines; i++) {
        printf("Comp %d Label: %s \n", i, g_ComponentList[i].Label);
    }
    free(g_ComponentList);
    free(g_NodeList);
    free(g_Lines);
    printf("Complete\n");
    return 0;
}

