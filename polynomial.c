#include "polynomial.h"

int zeroCutter(struct Ring *ringInfo, void **coefficients, int degree) {
    int i;
    for (i = degree; i > 0; --i) {
        if(! ringInfo->isEqual(ringInfo->zero, coefficients[i-1]))
            break;
    }
    return i;
}
struct Polynomial* FromValues(struct Ring *ringInfo, void **values, int degree) {
    struct Polynomial *polyn = (struct Polynomial*) malloc(sizeof(struct Polynomial));
    polyn->degree = zeroCutter(ringInfo, values, degree);
    for (int i = polyn->degree; i < degree; ++i) {
        free(*(values+i));
    }
    polyn->coefficients = (void**)realloc(values, sizeof(void*) * polyn->degree);
    polyn->ring = ringInfo;
    return polyn;
}

struct Polynomial* ZeroPolynomial(struct Ring *ringInfo) {
    struct Polynomial *polyn = (struct Polynomial*) malloc(sizeof(struct Polynomial));
    polyn->degree = 0;
    polyn->coefficients = NULL;
    polyn->ring = ringInfo;
    return polyn;
}

void DeletePolynomial(struct Polynomial* polyn) {
    if (polyn == NULL) return;
    for (int i = 0; i < polyn->degree; ++i) {
        free(polyn->coefficients[i]);
    }
    free(polyn->coefficients);
    DeleteRing(polyn->ring);
    free(polyn);
}

struct Polynomial* sumWithSortedDegrees(const struct Polynomial *maxPolyn, const struct Polynomial *minPolyn) {
    void **coefficients = (void**)malloc(sizeof(void*) * maxPolyn->degree);
    int i;
    for (i = 0; i < minPolyn->degree; ++i) {
        coefficients[i] = maxPolyn->ring->sum((maxPolyn->coefficients[i]), (minPolyn->coefficients[i]));
    }
    for (; i < maxPolyn->degree; ++i) {
        coefficients[i] = elementCopy(maxPolyn->ring, maxPolyn->coefficients[i]);
    }

    return FromValues(ringCopy(maxPolyn->ring), coefficients, maxPolyn->degree);
}

struct Polynomial* mult(const struct Polynomial *polyn1, const struct Polynomial *polyn2) {
    int len = polyn1->degree + polyn2->degree - 1;
    if (len == -1) len = 0; // if polyn1's and polyn2's degrees are 0
    void **coefficients = (void**)malloc(sizeof(void*) * len);
    for (int i = 0; i < len; ++i) {
        coefficients[i] = elementCopy(polyn1->ring, polyn1->ring->zero);
    }
    for (int i = 0; i < polyn1->degree; ++i) {
        for (int j = 0; j < polyn2->degree; ++j) {
            void *t = coefficients[i+j];
            void *a = polyn1->ring->mult(polyn1->coefficients[i], polyn2->coefficients[j]);
            coefficients[i + j] = polyn1->ring->sum(coefficients[i+j], a);
            free(a);
            free(t);
        }
    }
    return FromValues(ringCopy(polyn1->ring), coefficients, len);
}

struct Polynomial* sumPolynAndScal(const struct Polynomial *polyn, void *num) {
    if (polyn->degree >= 1) {
        void **coefficients = (void**)malloc(sizeof(void*) * polyn->degree);
        coefficients[0] = polyn->ring->sum(polyn->coefficients[0], num);
        for (int i = 1; i < polyn->degree; ++i) {
            coefficients[i] = elementCopy(polyn->ring, polyn->coefficients[i]);
        }
        return FromValues(ringCopy(polyn->ring), coefficients, polyn->degree);
    }
    else {
        void **coefficients = (void**)malloc(sizeof(void*));
        coefficients[0] = elementCopy(polyn->ring, num);
        return FromValues(ringCopy(polyn->ring), coefficients, 1);
    }
}


struct Polynomial* sum(const struct Polynomial *polyn1, const struct Polynomial *polyn2) {
    // compairing ring1 and ring2
    // if degree 0
    struct Polynomial* res;
    if (polyn1->degree > polyn2->degree) {
        res = sumWithSortedDegrees(polyn1, polyn2);
    }
    else {
        res = sumWithSortedDegrees(polyn2, polyn1);
    }
    return res;
}

struct Polynomial* multScal(const struct Polynomial *polyn, void *scal) {
    void **coefficients = (void**)malloc(sizeof(void*) * polyn->degree);
    for (int i = 0; i < polyn->degree; ++i) {
        coefficients[i] = polyn->ring->mult(polyn->coefficients[i], scal);
    }
    return FromValues(ringCopy(polyn->ring), coefficients, polyn->degree);
}

void* calculation(const struct Polynomial *polyn, void *value) { // calculated by Horner's method
    void *res = elementCopy(polyn->ring, polyn->ring->zero);
    for (int i = polyn->degree - 1; i >= 0; --i) {
        void *t = res;
        void *a = polyn->ring->mult(res, value);
        res = polyn->ring->sum(a, polyn->coefficients[i]);
        free(t);
        free(a);
    }
    return res;
}


struct Polynomial* composition(const struct Polynomial *polyn1, const struct Polynomial *polyn2) {
    struct Polynomial *res = ZeroPolynomial(ringCopy(polyn1->ring));
    for (int i = polyn1->degree - 1; i >= 0; --i) {
        struct Polynomial *t = res;
        res = mult(res, polyn2);
        struct Polynomial *a = res;
        res = sumPolynAndScal(res, polyn1->coefficients[i]);
        DeletePolynomial(t);
        DeletePolynomial(a);
    }
    return res;
}

int polynCmp(const struct Polynomial *polyn1, const struct Polynomial *polyn2) { // 1 if equal; 0 if different
    if (polyn1->degree != polyn2->degree)
        return 0;
    for (int i = 0; i < polyn1->degree; ++i) {
        if (!polyn1->ring->isEqual(polyn1->coefficients[i], polyn2->coefficients[i])) {
            return 0;
        }
    }
    return 1;
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
    int i;
    for (i = polyn->degree - 1; i >= 0; --i) {
        buff = polyn->ring->string(polyn->coefficients[i]); // add coefficient

        if (i) { // if i != 0
            degreeString = malloc(sizeof(char) * (digitCounter(i) + 1));
            sprintf(degreeString, "%d", i); // add degree
            buff = realloc(buff, sizeof(char) * (strlen(buff) + strlen(degreeString) + 7) );
            strcat(buff, "x^"); // add x^degree
            strcat(buff, degreeString);
            free(degreeString);
        }
        else { // if i == 0
            buff = realloc(buff, sizeof(char) * (strlen(buff) + 5) );
        }
        strcat(buff, " + ");
        str = realloc(str, sizeof(char) * (len+1+strlen(buff)));
        strcat(str, buff);
        len = strlen(str);
        free(buff);
    }

    if (polyn->degree>0) {
        str[strlen(str)-3] = 0;
    }
    str = realloc(str, sizeof(char) * (strlen(str)+1));
    return str;
}
