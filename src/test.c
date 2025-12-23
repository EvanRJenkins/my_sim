#include <stdio.h>
#include "imaginarymath.h"
#include "circuit.h"

float TestFunction(void) {
    return 5.0f;
}
int main(void) {
    Component_t *Comp1 = COMP_New(NULL, 47.0e-6f, CAPACITOR);
    Component_t *Comp2 = COMP_New(NULL, 100.0e-3f, INDUCTOR);
    Component_t *Comp3 = COMP_New(TestFunction, 0.0f, ACTIVE);
    Node_t *Node1 = CIRCUIT_NewNode(Comp1, NULL, NULL);
    printf("Node1 Label: %c, Impedance: %p\n", Node1->Label, (void *) Comp3->Value.ActiveFunction);
    free(Comp1);
    free(Comp2);
    free(Node1);
    return 0;
}

