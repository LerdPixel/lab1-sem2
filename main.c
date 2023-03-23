#include <stdio.h>
#include <stdlib.h>
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
    int a[] = {1, 1, 2};
    int l = 3;
    struct Polynomial* p1 = FromValues(CreateIntRing(), toVoidPointerArray(a, l), l);
    return 0;
}
