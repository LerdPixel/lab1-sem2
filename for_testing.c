#include "for_testing.h"

void prt(struct Polynomial* polyn) {
    char *str;
    printf("%s\n", str = polynToString(polyn));
    free(str);
}

void **fromIntToVoidPointerArray(int *array, int length) {
    void **voidArray = malloc(sizeof(void *) * length);
    for (int i = 0; i < length; ++i) {
        int *element = malloc(sizeof(int));
        *element = array[i];
        voidArray[i] = (void *) element;
    }
    return voidArray;
}

void **fromDoubleToVoidPointerArray(double *array, int length) {
    void **voidArray = malloc(sizeof(void *) * length);
    for (int i = 0; i < length; ++i) {
        double *element = malloc(sizeof(double));
        *element = array[i];
        voidArray[i] = (void *) element;
    }
    return voidArray;
}

struct Polynomial* polynCreator(void* array, int length, int type) {
    if (array == NULL) {
        switch (type) {
            case 1:
                return ZeroPolynomial(CreateIntRing());
                break;
            case 2:
                return ZeroPolynomial(CreateDoubleRing());
            default:
                return NULL;
        }
    }
    else {
        switch (type) {
            case 1:
                return FromValues(CreateIntRing(), fromIntToVoidPointerArray(array, length), length);
                break;
            case 2:
                return FromValues(CreateDoubleRing(), fromDoubleToVoidPointerArray(array, length), length);
            default:
                return NULL;
        }
    }
}
