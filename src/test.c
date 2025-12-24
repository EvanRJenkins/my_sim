#include "msnlparser.h"

int main(void) {
    Line_t *Lines = MSNL_ReadFile("test.txt");
    unsigned int i = 0;
    for (i = 0; i < g_LineIndex; i++) {
        printf("%s", Lines[i].Data);
    }
    free(Lines);
    printf("Complete");
    return 0;
}

