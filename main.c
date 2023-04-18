#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "array_input.h"
#include "polynomial.h"
#include "for_testing.h"




int main(int argc, char const *argv[]) {
    double a[] = {1.5};
    double b[] = {-1.3, 2, -1};
    int la = 1;
    int lb = 3;
    int *n = malloc(sizeof(int));
    *n = 10;
    struct Polynomial* p1 = FromValues(CreateDoubleRing(), fromDoubleToVoidPointerArray(a, la), la);
    struct Polynomial* p2 = polynCreator(b, 3, 2);
    struct Polynomial* p3 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p4 = sum(p1,p2);
    printf("cmp = %d\n", polynCmp(p4,p2));
    prt(p1);
    prt(p2);
    prt(p3);
    prt(p4);
    DeletePolynomial(p4);
    DeletePolynomial(p3);
    DeletePolynomial(p2);
    DeletePolynomial(p1);
    free(n);
    return 0;
}
