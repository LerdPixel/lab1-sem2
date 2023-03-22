#ifndef INT_VECTOR3
#define INT_VECTOR3

void* sumInt(void *a, void *b) {
    int* ia = (int*)a;
	int* ib = (int*)b;
    int *r = malloc(sizeof(int));
    *r = *ia + *ib;
    return (void *)r;
}

#endif
