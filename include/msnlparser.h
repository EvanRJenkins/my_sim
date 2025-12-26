#ifndef MSNLPARSER_H
#define MSNLPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "circuit.h"
/*
Line type and definitions
*/
#ifndef MAX_LINE_LENGTH
    #define MAX_LINE_LENGTH 100
#endif
// Line struct type
typedef struct Line {
    char Data[MAX_LINE_LENGTH];
} Line_t;
// Globals to track line index
extern Line_t *g_Lines;
extern Component_t *g_ComponentList;
extern Node_t *g_NodeList;
extern unsigned int g_NumNodesMax;
extern unsigned int g_NodeIndex;
extern unsigned int g_LineIndex;
extern unsigned int g_NumLines;

// Max number of chars in component label before '\0'
#ifndef MAX_LABEL_LENGTH
    #define MAX_LABEL_LENGTH 2
#endif

// Open file and read it
void MSNL_ReadFile(const char *file_name_string);
// Allocate memory for global component list
void MSNL_MakeComponentList();
// Allocate memory for global component list
void MSNL_MakeNodeList();
// Consolidate previous functions
void MSNL_GetCircuitFromFile(const char *target_file_string);
// Make component from line description
void MSNL_ParseLine(char *target_line);
/*
SAMPLE COMPONENT DESCRIPTION LINE IN MSNL FORMAT

*/


#endif
