#include "interface.h"

void freePolyns(struct Polynomial **polyns) {
    for (int i = 0; i < ARRAY_AMOUNT; ++i) {
        DeletePolynomial(polyns[i]);
    }
}


void printCommandMessage() {
	printf("\t<<< manual >>>\n h - help (open manual)\n i <polynomial num> - input (input polynomial)\n r <polynomial num> - random input (input random array in range diaposon) <beta> \n p <polynomial number> - print (print polynomial)\n c <polynomial number> - calculate the value of polynomial from a value\n m <first polynomial> <second polynomial> <result polynomial> - multiplication of the first polynomial by the second, result is written in the result polynomial\n o <first polynomial> <second polynomial> <result polynomial> - composition of polynomials\n s <first polynomial> <second polynomial> <result polynomial> - sum of polynomials\n x <first polynomial> <second polynomial> <result polynomial> - scalar product of polynomials\n q - quit\n");
}

int interface() {
    setbuf(stdout, NULL);
    char command;
    char str_command[50];
    int lengths[ARRAY_AMOUNT], arrayNumber, lowerBound, highBound, types[ARRAY_AMOUNT], arrayNumber1, arrayNumber2, arrayNumberRes;
    int *arrInt;
    double *arrDouble;
    struct Polynomial *polyns[ARRAY_AMOUNT];
    void *n, *resNum;
    for (int i = 0; i < ARRAY_AMOUNT; ++i) {
        polyns[i] = NULL;
        lengths[i] = -1;
    }
    printCommandMessage();
    while (1) { // main loop //
        if (inputCommand(str_command)) {
            freePolyns(polyns);
            return 1;
        }
        command = str_command[0];
        switch (command) {
            case 'h':
                printCommandMessage();
                break;
            case 'i':
                if (arrayNumberInput(&arrayNumber)) break; // array num input, check

                if (polyns[arrayNumber] != NULL) {
                    DeletePolynomial(polyns[arrayNumber]); // reinitialise array
                }

                if (typeInput(types + arrayNumber)) break; // types - input type
                if (lengthInput(lengths + arrayNumber)) break; // &length[0] - input len
                if (types[arrayNumber] == 1) {
                    polyns[arrayNumber] = polynCreator(arrInt = input(lengths[arrayNumber]), lengths[arrayNumber], types[arrayNumber]);
                    free(arrInt);
                }
                if (types[arrayNumber] == 2) {
                    polyns[arrayNumber] = polynCreator(arrDouble = inputDouble(lengths[arrayNumber]), lengths[arrayNumber], types[arrayNumber]);
                    free(arrDouble);
                }
                if (polyns[arrayNumber] == NULL && lengths[arrayNumber]) {
                    freePolyns(polyns);
                    return 1;
                }
                break;
            case 'r':
                if (arrayNumberInput(&arrayNumber)) break; // array num input, check

                if (polyns[arrayNumber] != NULL) {
                    DeletePolynomial(polyns[arrayNumber]); // reinitialise array
                }
                types[arrayNumber] = 1;
                if (randDataInput(lengths + arrayNumber, &lowerBound, &highBound)) break; // &length[0] - input len
                polyns[arrayNumber] = polynCreator(generateRandomArray(lengths[arrayNumber], lowerBound, highBound), lengths[arrayNumber], types[arrayNumber]);
                if (polyns[arrayNumber] == NULL) {
                    freePolyns(polyns);
                    return 1;
                }
                break;
            case 'p': // print array
                if (arrayNumberInput(&arrayNumber)) break; // array num input, check
                if (polyns[arrayNumber] == NULL) {
                    printf("array #%d not defined\n", arrayNumber);

                    break;
                }
                prt(polyns[arrayNumber]);
                break;

            case 's': // sum
                if (arrayNumberInput(&arrayNumber1)) break; // array 1 num input, check
                if (arrayNumberInput(&arrayNumber2)) break; // array 2 num input, check
                if (arrayNumberInput(&arrayNumberRes)) break; // res array num input, check
                DeletePolynomial(polyns[arrayNumberRes]);
                if (types[arrayNumber1] != types[arrayNumber2]) {
                    printf("I can't sum different types!\n");
                    break;
                }
                polyns[arrayNumberRes] = sum(polyns[arrayNumber1], polyns[arrayNumber2]);
                if (polyns[arrayNumberRes] == NULL) {
                    freePolyns(polyns);
                    return 1;
                }
                break;
            case 'm': // multiplication
                if (arrayNumberInput(&arrayNumber1)) break; // array 1 num input, check
                if (arrayNumberInput(&arrayNumber2)) break; // array 2 num input, check
                if (arrayNumberInput(&arrayNumberRes)) break; // res array num input, check
                DeletePolynomial(polyns[arrayNumberRes]);
                if (types[arrayNumber1] != types[arrayNumber2]) {
                    printf("I can't multiply different types!\n");
                    break;
                }
                polyns[arrayNumberRes] = mult(polyns[arrayNumber1], polyns[arrayNumber2]);
                if (polyns[arrayNumberRes] == NULL) {
                    freePolyns(polyns);
                    return 1;
                }
                break;
            case 'x': // scalar multiplication
                if (arrayNumberInput(&arrayNumber1)) break; // array 1 num input, check
                if (arrayNumberInput(&arrayNumberRes)) break; // res array num input, check
                if (types[arrayNumber1] == 1) {
                    int *a = malloc(sizeof(int));
                    intSafeInput(a);
                    n = (void*)a;
                }
                if (types[arrayNumber1] == 2) {
                    double *a = malloc(sizeof(double));
                    doubleSafeInput(a);
                    n = (void*)a;
                }
                DeletePolynomial(polyns[arrayNumberRes]);
                polyns[arrayNumberRes] = multScal(polyns[arrayNumber1], n);
                free(n);
                if (polyns[arrayNumberRes] == NULL) {
                    freePolyns(polyns);
                    return 1;
                }
                break;
            case 'o': // composition
                if (arrayNumberInput(&arrayNumber1)) break; // array 1 num input, check
                if (arrayNumberInput(&arrayNumber2)) break; // array 2 num input, check
                if (arrayNumberInput(&arrayNumberRes)) break; // res array num input, check
                DeletePolynomial(polyns[arrayNumberRes]);
                if (types[arrayNumber1] != types[arrayNumber2]) {
                    printf("I can't multiply different types!\n");
                    break;
                }
                polyns[arrayNumberRes] = composition(polyns[arrayNumber1], polyns[arrayNumber2]);
                if (polyns[arrayNumberRes] == NULL) {
                    freePolyns(polyns);
                    return 1;
                }
                break;
            case 'c': // calculation
                if (arrayNumberInput(&arrayNumber1)) break; // array 1 num input, check
                if (types[arrayNumber1] == 1) {
                    int *a = malloc(sizeof(int));
                    intSafeInput(a);
                    n = (void*)a;
                }
                if (types[arrayNumber1] == 2) {
                    double *a = malloc(sizeof(double));
                    doubleSafeInput(a);
                    n = (void*)a;
                }
                resNum = calculation(polyns[arrayNumber1], n);
                char *str = polyns[arrayNumber1]->ring->string(resNum);
                printf("%s\n", str);
                free(str);
                free(n);
                free(resNum);
                break;
            case 'q': // quit
                freePolyns(polyns);
                return 0;
            default:
                printf("Incorrect command.\n");
        }
    }
    freePolyns(polyns);
    return 0;

}
