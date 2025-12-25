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
extern Component_t *g_ComponentList;
extern Node_t *g_NodeList;
extern unsigned int g_NumberOfNodes;
extern unsigned int g_LineIndex;

// Max number of chars in component label before '\0'
#ifndef MAX_LABEL_LENGTH
    #define MAX_LABEL_LENGTH 2
#endif

// Open file and read it
Line_t *MSNL_ReadFile(const char *file_name_string);
// Allocate memory for global component list
void MSNL_MakeComponentList();
// Make component from line description
void MSNL_ParseLine(char *target_line);
/*
SAMPLE COMPONENT DESCRIPTION LINE IN MSNL FORMAT

*/


#endif
