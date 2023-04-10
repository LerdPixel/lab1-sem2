
#include "ring.h"


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
    free(ringInfo);
}

struct Ring* ringCopy(struct Ring* ring) {
    struct Ring* ringInfo = malloc(sizeof(struct Ring));
    ringInfo->size = ring->size;
	ringInfo->sum = ring->sum;
	ringInfo->zero = ring->sum(ring->zero, ring->zero);
	ringInfo->minus = ring->minus;
	ringInfo->mult = ring->mult;
	ringInfo->one = ring->sum(ring->one, ring->zero);
    ringInfo->isEqual = ring->isEqual;
    ringInfo->string = ring->string;
    return ringInfo;

}
