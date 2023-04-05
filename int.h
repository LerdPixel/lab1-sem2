#ifndef INT_VECTOR3
#define INT_VECTOR3
#define ENOUGH 12

void* sumInt(void *a, void *b) {
    int* ia = (int*)a;
	int* ib = (int*)b;
    int *r = malloc(sizeof(int));
    *r = *ia + *ib;
    return (void *)r;
}

void* multInt(void *a, void *b) {
    int* ia = (int*)a;
	int* ib = (int*)b;
    int *r = malloc(sizeof(int));
    *r = *ia + *ib;
    return (void *)r;
}

void* minusInt(void *a) {
    int* ia = (int*)a;
    int *r = malloc(sizeof(int));
    *r = - *ia;
    return (void *)r;
}

char* intToString(void *number) {
    char *str = malloc(ENOUGH * sizeof(char));
    int *intNumber = (int *)number, len;
    sprintf(str, "%d", *intNumber);
    len = strlen(str);
    str = realloc(str, (len + 1) * sizeof(char));
    return str;
}

int intIsEqual(void *a, void *b) {
    int* ia = (int*)a;
	int* ib = (int*)b;
    return (*ia == *ib);
}

struct Ring* CreateIntRing() {
    int *intZero = malloc(sizeof(int *));
    int *intOne = malloc(sizeof(int *));
    *intZero = 0;
    *intOne = 1;
    size_t size = sizeof(int);
    return CreateRing(size, sumInt, multInt, minusInt, (void *)intZero, (void *)intOne, intIsEqual, intToString);
}



#endif
