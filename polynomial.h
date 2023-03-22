#ifndef POLYNOMIAL
#define POLYNOMIAL

struct Polynomial {
    struct Ring *ring;
    void *coefficients;
    int degree;
};

struct Vector3* scanFromValues(struct Ring ringInfo) {
    int degree = lengthInput();

    struct Polynomial polynom = malloc(sizeof(struct Polynomial));
    polynom->ring = ringInfo;
    polynom->coefficients = values;
    polynom->degree = degree;
    return polynom;
}



struct Vector3* FromValues(struct Ring ringInfo, void *values, int degree) {
    struct Polynomial polynom = malloc(sizeof(struct Polynomial));
    polynom->ring = ringInfo;
    polynom->coefficients = values;
    polynom->degree = degree;
    return polynom;
}



#endif
