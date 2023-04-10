#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "array_input.h"
#include "polynomial.h"

void **toVoidPointerArray(int *array, int length) {
    void **voidArray = malloc(sizeof(void *) * length);
    for (int i = 0; i < length; ++i) {
        int *element = malloc(sizeof(int));
        *element = array[i];
        voidArray[i] = (void *) element;
    }
    return voidArray;
}
void prt(struct Polynomial* polyn) {
    char *str;
    printf("%s\n", str = polynToString(polyn));
    free(str);
}
int main(int argc, char const *argv[]) {
    int a[] = {1};
    int b[] = {1, 1, 1};
    int la = 1;
    int lb = 3;
    int *n = malloc(sizeof(int));
    *n = 10;
    struct Polynomial* p1 = FromValues(CreateIntRing(), toVoidPointerArray(a, la), la);
    struct Polynomial* p2 = FromValues(CreateIntRing(), toVoidPointerArray(b, lb), lb);
    struct Polynomial* p3 = mult(p1, p2);
    struct Polynomial* p4 = sum(p2,p3);
    prt(p1);
    prt(p2);
    prt(p3);
    prt(p4);
    DeletePolynomial(p4);
    DeletePolynomial(p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    free(n);
    return 0;
}
