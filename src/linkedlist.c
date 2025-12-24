#include "linkedlist.h"
// Global pointers to track list nodes
const Line_t *pFirstNode = NULL;
Line_t *pNewestNode = NULL;
// Initializer function to add a node
// Cast the return value to desired type!
Line_t *LNKLST_NewLine() {
    // Allocate memory for new node
    Line_t *result = (Line_t *) malloc(sizeof(Line_t));
    result->Next = NULL;
    // If first node (pNewestNode is NULL)
    if ((pNewestNode == NULL) && (pFirstNode == NULL)) {
        pFirstNode = result;
        pNewestNode = result;
    }
    // Update Next ptr of previous node
    pNewestNode->Next = result;
    // Update pNewestNode
    pNewestNode = result;
    // Return new node ptr
    return result;
}
