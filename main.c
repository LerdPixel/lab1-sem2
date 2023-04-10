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

int main(int argc, char const *argv[]) {
    int a[] = {-2, 1, 1, 0};
    int b[] = {7, 6, -1, -2};
    int la = 4;
    int lb = 4;
    int *n = malloc(sizeof(int));
    *n = 0;
    struct Polynomial* p1 = FromValues(CreateIntRing(), toVoidPointerArray(a, la), la);
    struct Polynomial* p2 = FromValues(CreateIntRing(), toVoidPointerArray(b, lb), lb);
    struct Polynomial* p3 = multScal(p1,(void*)n);
    struct Polynomial* p4 = sum(p1,p3);
    char* str;
    printf("%s\n", str = polynToString(p3));
    free(str);
    printf("%s\n", str = polynToString(p1));
    free(str);

    DeletePolynomial(p4);
    DeletePolynomial(p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    free(n);
    return 0;
}
