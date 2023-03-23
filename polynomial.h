#ifndef POLYNOMIAL
#define POLYNOMIAL
#include <stdlib.h>
struct Polynomial {
    struct Ring *ring;
    void **coefficients;
    int degree;
};
/*
struct Polynomial* scanFromValues(struct Ring ringInfo) {
    int degree = lengthInput();
    void *array = voidInput(degree);
    return FromValues(ringInfo, array, degree);
}
*/
struct Polynomial* FromValues(struct Ring *ringInfo, void **values, int degree) {
    struct Polynomial *polynom = (struct Polynomial*) malloc(sizeof(struct Polynomial));
    polynom->ring = ringInfo;
    polynom->coefficients = values;
    polynom->degree = degree;
    return polynom;
}

struct Polynomial* sum(struct Polynomial *polyn1, struct Polynomial *polyn2) {
    // compairing ring1 and ring2
    // if degree 0
    int maxDegree = polyn1->degree > polyn2->degree ? polyn1->degree : polyn2->degree;
    void **coefficients = malloc(sizeof(void*) * maxDegree);
    for (int i = 0; i < maxDegree; ++i) {
        coefficients[i] = polyn1->ring->sum((polyn1->coefficients+i), (polyn2->coefficients+i));
    }
    return FromValues(polyn1->ring, coefficients, maxDegree);
}

#endif
