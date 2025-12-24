#include <stdio.h>
#include "linkedlist.h"


int main(void) {
    Line_t *Node1 = LNKLST_NewLine();
    Line_t *Node2 = LNKLST_NewLine();
    printf("Next: %p, pNewestNode: %p\n", Node1->Next, (void *) pNewestNode);
    free(Node1);
    free(Node2);
    return 0;
}

