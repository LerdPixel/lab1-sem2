#ifndef FOR_TESTING
#define FOR_TESTING
#include "polynomial.h"
#include <stdlib.h>

void prt(struct Polynomial* polyn);

void **fromIntToVoidPointerArray(int *array, int length);

void **fromDoubleToVoidPointerArray(double *array, int length);

struct Polynomial* polynCreator(void* array, int length, int type);

#endif
