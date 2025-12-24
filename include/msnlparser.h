#include <stdio.h>
#include <string.h>
#include "circuit.h"
#include "line.h"
// File pointer for file I/O
extern FILE *fptr;
// Open file and read it
Line_t *MSNL_ReadFile(const char *file_name_string);

