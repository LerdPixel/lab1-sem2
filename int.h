#ifndef INT_POLYN
#define INT_POLYN

#include "ring.h"
#define ENOUGH 20

void* sumInt(void *a, void *b);

void* multInt(void *a, void *b);

void* minusInt(void *a);

char* intToString(void *number);

int intIsEqual(void *a, void *b);

struct Ring* CreateIntRing(void);



#endif
