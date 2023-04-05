#ifndef RING
#define RING

struct Ring {
    size_t size;
    void* (*sum)(void*, void*);
    void* zero;
    void* (*minus)(void*);
    void* (*mult)(void*, void*);
    void* one;
    int (*isEqual)(void*, void*); /* return 1 if values are equal, 0 if they don't */
    char* (*string)(void*);
};


struct Ring* CreateRing(size_t size, void* (*sum)(void*, void*), void* (*mult)(void*, void*), void* (*minus)(void*), void* zero, void* one, int (*isEqual)(void*, void*), char* (*string)(void*)) {
	struct Ring* ringInfo = malloc(sizeof(struct Ring));
	ringInfo->size = size;
	ringInfo->sum = sum;
	ringInfo->zero = zero;
	ringInfo->minus = minus;
	ringInfo->mult = mult;
	ringInfo->one = one;
    ringInfo->isEqual = isEqual;
    ringInfo->string = string;
    return ringInfo;
}

void DeleteRing(struct Ring* ringInfo) {
    free(ringInfo->zero);
    free(ringInfo->one);
}

struct Ring* ringCopy(struct Ring* ring) {
    struct Ring* ringInfo = malloc(sizeof(struct Ring));
    ringInfo->size = ring->size;
	ringInfo->sum = ring->sum;
	ringInfo->zero = ring->zero;
	ringInfo->minus = ring->minus;
	ringInfo->mult = ring->mult;
	ringInfo->one = ring->one;
    ringInfo->isEqual = ring->isEqual;
    ringInfo->string = ring->string;
    return ringInfo;

}


#endif
