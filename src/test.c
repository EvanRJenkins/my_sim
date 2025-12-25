#include "msnlparser.h"

int main(void) {
    Line_t *Lines = MSNL_ReadFile("test.txt");
    MSNL_MakeComponentList();
    unsigned int i = 0;
    for (i = 0; i < g_LineIndex; i++) {
        printf("%s", Lines[i].Data);
    }
    printf("Line before MSNL_ParseLine\n");
    MSNL_ParseLine(Lines[0].Data);
    printf("Complete");
    return 0;
}

