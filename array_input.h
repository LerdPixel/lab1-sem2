#ifndef ARRAY_INPUT
#define ARRAY_INPUT
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int intSafeInput(int *n);

int doubleSafeInput(double *n);

int inputCommand(char *str_command);

int lengthInput(int *length);

int indexInput(int *index, int len);

int indexInputForInsert(int *index, int len);

int arrayNumberInput(int *arrayNumber);

int randDataInput(int *length, int *lowerBound, int *highBound);

int *generateRandomArray(int len, int lowerBound, int highBound);

int typeInput(int *type);

int *input(int len);

double *inputDouble(int len);

#endif
