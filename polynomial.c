#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"



int zeroCutter(struct Ring *ringInfo, void **coefficients, int degree) {
    int i;
    for (i = degree; i > 0; --i) {
        if(! ringInfo->isEqual(ringInfo->zero, coefficients[i-1]))
            break;
    }
    return i;
}

struct Polynomial* FromValues(struct Ring *ringInfo, void **values, int degree) {
    struct Polynomial *polyn = (struct Polynomial*) malloc(sizeof(struct Polynomial));
    polyn->degree = zeroCutter(ringInfo, values, degree);
    for (int i = polyn->degree; i < degree; ++i) {
        free(*(values+i));
    }
    polyn->coefficients = (void**)realloc(values, sizeof(void*) * polyn->degree);
    polyn->ring = ringInfo;
    return polyn;
}

struct Polynomial* ZeroPolynomial(struct Ring *ringInfo) {
    struct Polynomial *polyn = (struct Polynomial*) malloc(sizeof(struct Polynomial));
    polyn->degree = 0;
    polyn->coefficients = NULL;
    polyn->ring = ringInfo;
    return polyn;
}

void DeletePolynomial(struct Polynomial* polyn) {
    for (int i = 0; i < polyn->degree; ++i) {
        free(polyn->coefficients[i]);
    }
    free(polyn->coefficients);
    DeleteRing(polyn->ring);
    free(polyn);
}

struct Polynomial* sumWithSortedCoefficients(const struct Polynomial *maxPolyn, const struct Polynomial *minPolyn) {
    void **coefficients = (void**)malloc(sizeof(void*) * maxPolyn->degree);
    int i;
    for (i = 0; i < minPolyn->degree; ++i) {
        coefficients[i] = maxPolyn->ring->sum((maxPolyn->coefficients[i]), (minPolyn->coefficients[i]));
    }
    for (; i < maxPolyn->degree; ++i) {
        coefficients[i] = maxPolyn->ring->sum(maxPolyn->coefficients[i], maxPolyn->ring->zero);
    }

    return FromValues(ringCopy(maxPolyn->ring), coefficients, maxPolyn->degree);
}

struct Polynomial* sum(const struct Polynomial *polyn1, const struct Polynomial *polyn2) {
    // compairing ring1 and ring2
    // if degree 0
    struct Polynomial* res;
    if (polyn1->degree > polyn2->degree) {
        res = sumWithSortedCoefficients(polyn1, polyn2);
    }
    else {
        res = sumWithSortedCoefficients(polyn2, polyn1);
    }
    return res;
}

struct Polynomial* multScal(const struct Polynomial *polyn, void* scal) {
    void **coefficients = (void**)malloc(sizeof(void*) * polyn->degree);
    for (int i = 0; i < polyn->degree; ++i) {
        coefficients[i] = polyn->ring->mult(polyn->coefficients[i], scal);
    }
    return FromValues(ringCopy(polyn->ring), coefficients, polyn->degree);
}

int digitCounter(int x) {
    int res = 0;
    while (x) {
        ++res;
        x /= 10;
    }
    return res;
}

char* polynToString(struct Polynomial *polyn) {
    char *str, *buff, *degreeString;
    str = malloc(sizeof(char));
    str[0] = 0;
    int len = 0;
    int i;
    for (i = polyn->degree - 1; i >= 0; --i) {
        buff = polyn->ring->string(polyn->coefficients[i]); // add coefficient

        if (i) {
            degreeString = malloc(sizeof(char) * (digitCounter(i) + 1));
            sprintf(degreeString, "%d", i); // add degree
            buff = realloc(buff, sizeof(char) * (strlen(buff) + strlen(degreeString) + 7) );
            strcat(buff, "x^"); // add x^degree
            strcat(buff, degreeString);
            free(degreeString);
        }
        else {
            buff = realloc(buff, sizeof(char) * (strlen(buff) + 5) );
        }
        strcat(buff, " + ");
        str = realloc(str, sizeof(char) * (len+1+strlen(buff)));
        strcat(str, buff);
        len = strlen(str);
        free(buff);
    }

    if (polyn->degree>0) {
        str[strlen(str)-3] = 0;
    }
    str = realloc(str, sizeof(char) * (strlen(str)+1));
    return str;
}
