#ifndef FOR_TESTING
#define FOR_TESTING
#include "polynomial.h"
#include <stdlib.h>

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
        default:
            return NULL;
    }
}

#endif
