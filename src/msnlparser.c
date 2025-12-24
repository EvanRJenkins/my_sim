#include "msnlparser.h"
// Open file and read it, return ptr to Lines array
Line_t *MSNL_ReadFile(const char *file_name_string) {
    // Open the file in read mode
    FILE *fptr = fopen(file_name_string, "r");
    // Error if file opening failed
    if (fptr == NULL) {
        printf("Error: failed to open file %s. Program terminated.\n", file_name_string);
        exit(EXIT_FAILURE);
    }
    // Count lines in file
    char c;
    unsigned int count = 0;
    for (c = fgetc(fptr); c != EOF; c = fgetc(fptr)) if (c == '\n') count++;
    // Assign number of lines counted to global line index
    g_LineIndex = count;
    // Allocate Lines array
    Line_t *result = (Line_t *) malloc(sizeof(Line_t) * g_LineIndex);
    // Reset read ptr
    rewind(fptr);
    for (count = 0; count < g_LineIndex; ++count) {
        // Access the array at index [count], then the .Data member
        fgets(result[count].Data, MAX_LINE_LENGTH, fptr);
    }
    // Close the file
    fclose(fptr);
    return result;
}

