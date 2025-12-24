#ifndef MSNLPARSER_H
#define MSNLPARSER_H

#include <stdio.h>
#include <string.h>
#include "circuit.h"
#include "line.h"
// Max number of chars in component label before '\0'
#ifndef MAX_LABEL_LENGTH
    #define MAX_LABEL_LENGTH 2
#endif

// Open file and read it
Line_t *MSNL_ReadFile(const char *file_name_string);
// Allocate memory for global component list
Component_t *MSNL_MakeComponentList();
// Make component from line description
Component_t *MSNL_GetComponent(Line_t * target);
/*
SAMPLE COMPONENT DESCRIPTION LINE IN MSNL FORMAT

*/


#endif
