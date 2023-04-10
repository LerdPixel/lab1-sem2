#ifndef INT_VECTOR3
#define INT_VECTOR3

#include "ring.h"
#define ENOUGH 12

void* sumInt(void *a, void *b);

void* multInt(void *a, void *b);

void* minusInt(void *a);

char* intToString(void *number);

int intIsEqual(void *a, void *b);

struct Ring* CreateIntRing(void);



#endif
