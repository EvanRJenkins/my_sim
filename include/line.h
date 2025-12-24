#include <stdlib.h>
/*
This file provides the line type and definitions
*/
#ifndef MAX_LINE_LENGTH
    #define MAX_LINE_LENGTH 100
#endif
// Line struct type
typedef struct Line {
    char Data[MAX_LINE_LENGTH];
} Line_t;
// Globals to track line index
extern unsigned int g_LineIndex;

