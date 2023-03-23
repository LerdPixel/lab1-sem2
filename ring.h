#ifndef RING
#define RING

struct Ring {
    size_t size;
    void* (*sum)(void*, void*);
    void* zero;
    void* (*minus)(void*);
    void* (*mult)(void*, void*);
    void* one;
};


struct Ring* CreateRing(size_t size, void* (*sum)(void*, void*), void* (*mult)(void*, void*), void* (*minus)(void*), void* zero, void* one) {
	struct Ring* ringInfo = malloc(sizeof(struct Ring));
	ringInfo->size = size;
	ringInfo->sum = sum;
	ringInfo->zero = zero;
	ringInfo->minus = minus;
	ringInfo->mult = mult;
	ringInfo->one = one;
    return ringInfo;
}


#endif
