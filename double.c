#include "double.h"

void* sumDouble(void *a, void *b) {
    double* ia = (double*)a;
	double* ib = (double*)b;
    double *r = malloc(sizeof(double));
    *r = *ia + *ib;
    return (void *)r;
}

void* multDouble(void *a, void *b) {
    double* ia = (double*)a;
	double* ib = (double*)b;
    double *r = malloc(sizeof(double));
    *r = *ia * *ib;
    return (void *)r;
}

void* minusDouble(void *a) {
    double* ia = (double*)a;
    double *r = malloc(sizeof(double));
    *r = - *ia;
    return (void *)r;
}

char* doubleToString(void *number) {
    char *str = malloc(30 * sizeof(char));
    double *doubleNumber = (double *)number, len;
    sprintf(str, "%lf", *doubleNumber);
    len = strlen(str);
    str = realloc(str, (len + 1) * sizeof(char));
    return str;
}

int doubleIsEqual(void *a, void *b) {
    double* ia = (double*)a;
	double* ib = (double*)b;
    if (*ia == *ib)
        return 1;
    return 0;
}

struct Ring* CreateDoubleRing() {
    double *doubleZero = malloc(sizeof(double));
    double *doubleOne = malloc(sizeof(double));
    *doubleZero = 0;
    *doubleOne = 1;
    void* vOne = (void*)doubleOne;
    void* vZero = (void*)doubleZero;
    size_t size = sizeof(double);
    return CreateRing(size, sumDouble, multDouble, minusDouble, vZero, vOne, doubleIsEqual, doubleToString);
}
