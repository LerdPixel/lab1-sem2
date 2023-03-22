#ifndef ARRAY_INPUT
#define ARRAY_INPUT
#include <stdlib.h>

int intSafeInput(int *n) {
	int sres = scanf("%d", n);
	while (sres != 1) {
		if (sres == EOF)
		return EOF;
		if (sres != 1) {
			scanf("%*[^\n]");
			puts("Wrong integer input format\n");
		}
		sres = scanf("%d", n);
	}
	return 0;
}
int inputCommand(char *str_command) {
	int scan_res = scanf("%s", str_command); // command input in dialog menu
	if (scan_res == EOF) {
		return 1;
	}
	return 0;
}
int lengthInput(int *length) {
    printf("Input array length: ");
    if (intSafeInput(length) == EOF) {
        return 1;
    }
    if (*length < 0) {
        printf("Length must be more than 0.\n");
        return 1;
    }
    return 0;
}
int indexInput(int *index, int len) {
    printf("Input index: ");
    int flag = 0;
    do {
        if (flag) {printf("Index can't be more than length (len = %d); or less than 0\nInput index: ", len);}
        flag = 1;
        if (intSafeInput(index) == EOF) return 1;
    }
    while (*index >= len || *index < 0);
    return 0;
}
int indexInputForInsert(int *index, int len) {
    printf("Input index: ");
    int flag = 0;
    do {
        if (flag) {printf("Index can't be less than 0\nInput index: ");}
        flag = 1;
        if (intSafeInput(index) == EOF) return 1;
    }
    while (*index < 0);
    return 0;
}
int arrayNumberInput(int *arrayNumber) {
    if (intSafeInput(arrayNumber) == EOF) {
        return 1;
    } // safe input
    if (*arrayNumber >= ARRAY_AMOUNT || *arrayNumber < 0) { // if out of range
        printf("Array number must be in range ( 0 - %d ) !\n", ARRAY_AMOUNT - 1);
        return 1;
    }
    return 0;
}
int randDataInput(int *length, int *lowerBound, int *highBound) {
    if (lengthInput(length))
        return 1;
    printf("Input random numbers's lower bound : ");
    if (intSafeInput(lowerBound) == EOF) {
        return 1;
    }
    printf("Input random numbers's higher bound : ");
    if (intSafeInput(highBound) == EOF) {
        return 1;
    }
    return 0;
}

int *generateRandomArray(int len, int lowerBound, int highBound) {
    int *arr = (int *)malloc(sizeof(int) * len);
    if (arr == NULL) { // memory check
        puts("no memory\n");
        return NULL;
    }
    int gap = highBound - lowerBound;
    if (!gap) {
        puts("Gap can't be 0.");
        return NULL;
    }
    gap = gap < 0 ? -gap : gap;
    for (int i = 0; i < len; ++i) {
        arr[i] = lowerBound + rand() % gap;
    }
    return arr;
}

int *input(int len) {
	int *arr = (int *)malloc(sizeof(int) * len);
    int res;
	if (arr == NULL) {
		puts("no memory\n");
		return NULL;
	}
	for (int i = 0; i < len; ++i) {
        printf("element %d = ", i);
        res = intSafeInput(arr+i);
        if (res == EOF) {
            puts("\ninput interrupted\n");
            return NULL;
        }
	}
	return arr;
}
#endif
