#include <stdlib.h>
/*
This file provides the linked list data structure
*/
#ifndef MAX_LINE_LENGTH
    #define MAX_LINE_LENGTH 100
#endif
// Generic list node struct
typedef struct ListNode {
    char Data[MAX_LINE_LENGTH];
    void *Next;
} Line_t;
// Globals to track linked list status
extern const Line_t *pFirstNode;
extern Line_t *pNewestNode;

// Initializer functinon to add a node
Line_t *LNKLST_NewLine();
