#ifndef POLYNOMIAL
#define POLYNOMIAL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"
#include "int.h"
#include "double.h"

struct Polynomial {
    struct Ring *ring;
    void **coefficients;
    int degree;
};

int zeroCutter(struct Ring *ringInfo, void **coefficients, int degree);

struct Polynomial* FromValues(struct Ring *ringInfo, void **values, int degree);

struct Polynomial* ZeroPolynomial(struct Ring *ringInfo);

void DeletePolynomial(struct Polynomial* polyn);

struct Polynomial* sum(const struct Polynomial *polyn1, const struct Polynomial *polyn2);

struct Polynomial* multScal(const struct Polynomial *polyn, void* scal);

struct Polynomial* mult(const struct Polynomial *polyn1, const struct Polynomial *polyn2);

void* calculation(const struct Polynomial *polyn, void *value);

int polynCmp(const struct Polynomial *polyn1, const struct Polynomial *polyn2);

struct Polynomial* sumPolynAndScal(const struct Polynomial *polyn, void *num);

struct Polynomial* composition(const struct Polynomial *polyn1, const struct Polynomial *polyn2);

int digitCounter(int x);

char* polynToString(struct Polynomial *polyn);

#endif
