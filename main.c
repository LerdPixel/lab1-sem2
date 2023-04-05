#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "array_input.h"

#include "ring.h"
#include "int.h"
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
    int a[] = {-2, 1, 1, 2};
    int b[] = {7, 6, 0};
    int l = 3;
    struct Polynomial* p1 = FromValues(CreateIntRing(), toVoidPointerArray(a, 4), 4);
    struct Polynomial* p2 = FromValues(CreateIntRing(), toVoidPointerArray(b, 3), 3);
    char *str;

    struct Polynomial* p3 = sum(p1, p2);
    printf("%s\n", str = polynToString(p1));
    free(str);
    printf("%s\n", str = polynToString(p2));
    free(str);
    printf("%s\n", str = polynToString(p3));
    free(str);
    return 0;
}
