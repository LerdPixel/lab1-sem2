#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "array_input.h"
#include "polynomial.h"




void **fromIntToVoidPointerArray(int *array, int length) {
    void **voidArray = malloc(sizeof(void *) * length);
    for (int i = 0; i < length; ++i) {
        int *element = malloc(sizeof(int));
        *element = array[i];
        voidArray[i] = (void *) element;
    }
    return voidArray;
}

struct Polynomial* polynCreator(int* array, int length, int type) {
    switch (type) {
        case 1:
            return FromValues(CreateIntRing(), fromIntToVoidPointerArray(array, length), length);
            break;
    }
}

void prt(struct Polynomial* polyn) {
    char *str;
    printf("%s\n", str = polynToString(polyn));
    free(str);
}

int main(int argc, char const *argv[]) {
    int a[] = {1};
    int b[] = {-1, 2, -1};
    int la = 1;
    int lb = 3;
    int *n = malloc(sizeof(int));
    *n = 10;
    struct Polynomial* p1 = FromValues(CreateIntRing(), fromIntToVoidPointerArray(a, la), la);
    struct Polynomial* p2 = polynCreator(b, 3, 1);
    struct Polynomial* p3 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p4 = sum(p3,p2);
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
