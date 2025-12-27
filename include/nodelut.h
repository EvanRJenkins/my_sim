#ifndef NODELUT_H
#define NODELUT_H

#include <stdlib.h> // For NULL
#include <math.h>
#include "msnlparser.h"

// LUT mapping structs
// New entry to table
typedef struct {
    char Name[MAX_LABEL_LENGTH + 1]; // String label
    char Letter; // Single char equivalent
} LabelMapEntry_t;

//Global Function Table
// Maps the text string to the function pointer.
extern LabelMapEntry_t *g_NodeTable;
// Allocate memory for NodeTable and populate entries
void NODELUT_MakeNodeTable();
// FOR TESTING: PRINT ALL PAIRS IN NODE TABLE
void NODELUT_PrintNodeTable();
#endif

