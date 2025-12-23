#include <stdio.h>
#include "imaginarymath.h"
#include "components.h"

float ConstantSource(float x) {
    return x;
}

int main(void) {
    comp_t *My_Component = COMP_New();
    COMP_InitINDUCTOR(My_Component, 100.0E-3f);  // 100 mH
    printf("%f+j%f\n", My_Component->Value.Z[0], My_Component->Value.Z[1]);
    free(My_Component);
    return 0;
}

