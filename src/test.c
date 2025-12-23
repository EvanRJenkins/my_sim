#include "imag.h"

int main(void) {
    float *test1 = IMAG_New();
    float *test2 = IMAG_New();
    IMAG_Init(test1, 2, 2);
    IMAG_Init(test2, 2, 2);
    float *quotient = IMAG_Div(test1, test2);
    free(test1);
    free(test2);
    printf("Result: %f  %fj\n", quotient[0], quotient[1]);
    free(quotient);
    return 0;
}
