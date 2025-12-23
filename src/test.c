#include "imag.h"
#include "comp.h"

float ConstantSource(float x) {
    return x;
}

int main(void) {
    float *My_Impedance = IMAG_New();
    IMAG_Init(My_Impedance, 1, 2);
    comp_t *My_Resistor = COMP_New();
    COMP_InitRESISTOR(My_Resistor, My_Impedance);
    free(My_Impedance);
    printf("%f+j%f\n", My_Resistor->Value.Z[0], My_Resistor->Value.Z[1]);
    free(My_Resistor);
    return 0;
}

