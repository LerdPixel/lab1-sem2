#ifndef DOUBLE_POLYN
#define DOUBLE_POLYN

#include "ring.h"


void* sumDouble(void *a, void *b);

void* multDouble(void *a, void *b);

void* minusDouble(void *a);

char* doubleToString(void *number);

int doubleIsEqual(void *a, void *b);

struct Ring* CreateDoubleRing(void);



#endif
