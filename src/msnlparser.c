#include "msnlparser.h"



// Read file
void MSNL_Read(const char *target) {
    fptr = fopen(target, "r");
    // Terminate if NULL fptr
    if (fptr == NULL) {
        printf("Error: Failed to open file. Program terminated.");
        exit(EXIT_FAILURE);
    }
    // Read each line_t
    while (fgets(lines[0], MAX_LINE_LENGTH, fptr) != NULL) {
        line_t
    }
}
