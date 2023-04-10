#ifndef RING
#define RING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ring {
    size_t size; // size in bytes
    void* (*sum)(void*, void*);
    void* zero;
    void* (*minus)(void*);
    void* (*mult)(void*, void*);
    void* one;
    int (*isEqual)(void*, void*); /* return 1 if values are equal, 0 if they don't */
    char* (*string)(void*);
};


struct Ring* CreateRing(size_t size, void* (*sum)(void*, void*), void* (*mult)(void*, void*), void* (*minus)(void*), void* zero, void* one, int (*isEqual)(void*, void*), char* (*string)(void*));

void DeleteRing(struct Ring* ringInfo);

struct Ring* ringCopy(struct Ring* ring);

void* elementCopy(struct Ring* ring, void* element);

#endif
