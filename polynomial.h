#ifndef POLYNOMIAL
#define POLYNOMIAL
#include "ring.h"
#include "int.h"

struct Polynomial {
    struct Ring *ring;
    void **coefficients;
    int degree;
};

int zeroCutter(struct Ring *ringInfo, void **coefficients, int degree);

struct Polynomial* FromValues(struct Ring *ringInfo, void **values, int degree);

struct Polynomial* ZeroPolynomial(struct Ring *ringInfo);

void DeletePolynomial(struct Polynomial* polyn);

struct Polynomial* sumWithSortedCoefficients(const struct Polynomial *maxPolyn, const struct Polynomial *minPolyn);

struct Polynomial* sum(const struct Polynomial *polyn1, const struct Polynomial *polyn2);

struct Polynomial* multScal(const struct Polynomial *polyn, void* scal);

int digitCounter(int x);

char* polynToString(struct Polynomial *polyn);

#endif
