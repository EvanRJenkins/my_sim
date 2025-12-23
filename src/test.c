#include <stdio.h>
#include "imaginarymath.h"
#include "circuit.h"


int main(void) {
    Component_t *Comp1 = COMP_New();
    COMP_InitRESISTOR(Comp1, 1000.0f);
    Component_t *Comp2 = COMP_New();
    COMP_InitCAPACITOR(Comp2, 47.0E-6f);
    Component_t *Comp3 = COMP_New();
    COMP_InitINDUCTOR(Comp3, 100.0E-3f);
    Node_t *Node1 = CIRCUIT_NewNode(Comp1, Comp2, Comp3);
    printf("Z1: %f", Node1->Connections[0]->Value.Z[0]);
    printf("Z2: %f", Node1->Connections[1]->Value.Z[1]);
    printf("Z3: %f", Node1->Connections[2]->Value.Z[1]);
    free(Comp1);
    free(Comp2);
    free(Comp3);
    return 0;
}

