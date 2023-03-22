#ifndef INT_VECTOR3
#define INT_VECTOR3

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



#endif
