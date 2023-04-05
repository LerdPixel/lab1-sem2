#ifndef POLYNOMIAL
#define POLYNOMIAL


struct Polynomial {
    struct Ring *ring;
    void **coefficients;
    int degree;
};
/*
struct Polynomial* scanFromValues(struct Ring ringInfo) {
    int degree = lengthInput();
    void *array = voidInput(degree);
    return FromValues(ringInfo, array, degree);
}
*/


struct Polynomial* FromValues(struct Ring *ringInfo, void **values, int degree) {
    struct Polynomial *polynom = (struct Polynomial*) malloc(sizeof(struct Polynomial));
    polynom->ring = ringInfo;
    polynom->coefficients = values;
    polynom->degree = degree;
    return polynom;
}

struct Polynomial* sumWithSortedCoefficients(const struct Polynomial *maxPolyn, const struct Polynomial *minPolyn) {
    void **coefficients = (void**)malloc(sizeof(void*) * maxPolyn->degree);
    int i;
    for (i = 0; i < minPolyn->degree; ++i) {
        coefficients[i] = maxPolyn->ring->sum((maxPolyn->coefficients[i]), (minPolyn->coefficients[i]));
    }
    for (; i < maxPolyn->degree; ++i) {
        coefficients[i] = maxPolyn->ring->sum(maxPolyn->coefficients[i], maxPolyn->ring->zero);
    }
    return FromValues(maxPolyn->ring, coefficients, maxPolyn->degree);
}

struct Polynomial* sum(const struct Polynomial *polyn1, const struct Polynomial *polyn2) {
    // compairing ring1 and ring2
    // if degree 0
    int maxDegree, minDegree;
    struct Polynomial* res;
    if (polyn1->degree > polyn2->degree) {
        res = sumWithSortedCoefficients(polyn1, polyn2);
    }
    else {
        res = sumWithSortedCoefficients(polyn2, polyn1);
    }
    return res;
}

int digitCounter(int x) {
    int res = 0;
    while (x) {
        ++res;
        x /= 10;
    }
    return res;
}

char* polynToString(struct Polynomial *polyn) {
    char *str, *buff, *degreeString;
    str = malloc(sizeof(char));
    str[0] = 0;
    int len = 0;
    int varLen = 0;
    int i;
    for (i = 0; i < polyn->degree; ++i) {
        buff = polyn->ring->string(polyn->coefficients[i]);
        degreeString = malloc(sizeof(char) * (digitCounter(i) + 1));

        sprintf(degreeString, "%d", i);
        buff = realloc(buff, sizeof(char) * (strlen(buff) + strlen(degreeString) + 7) );
        strcat(buff, "x^");
        strcat(buff, degreeString);
        strcat(buff, " + ");
        str = realloc(str, sizeof(char) * (len+1+strlen(buff)));
        strcat(str, buff);
        len = strlen(str);
        free(buff);
        free(degreeString);
    }

    if (i) {
        str[strlen(str)-3] = 0;
    }
    str = realloc(str, sizeof(char) * (strlen(str)+1));
    return str;
}

#endif
