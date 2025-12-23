#include <stdio.h>
#include "imaginarymath.h"
#include "circuit.h"


int main(void) {
    Component_t *Comp1 = COMP_New(NULL, 47.0e-6f, CAPACITOR);
    Node_t *Node1 = CIRCUIT_NewNode(Comp1, NULL, NULL);
    printf("Node1 Label: %c, Impedance: %f %fj\n", Node1->Label, Comp1->Value.Z[0], Comp1->Value.Z[1]);
    free(Comp1);
    free(Node1);
    return 0;
}

