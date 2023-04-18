#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "for_testing.h"
#define NUMBER_OF_TYPES 2
// test suite main variables
static int num_tests;
static int tests_passed;


static int current_tests;
static int current_tests_passed;

static int num_modules;
static int correct_modules;


static int rslt;

void TestStart(char *name) {
    current_tests++;
    rslt = 1;
    printf("-- Testing %s ... ", name);
}

void TestEnd() {
    if (rslt) current_tests_passed++;
    printf("%s\n", rslt ? "success" : "fail");
}

void HeaderTestStart(char *name) {
    current_tests = 0;
    current_tests_passed = 0;
    num_modules++;
    printf("\n---- Tests %s are starting\n", name);
}

void HeaderTestEnd() {
    num_tests += current_tests;
    tests_passed += current_tests_passed;
    printf("---- Module state: ");

    printf(" ( %d / %d ) -- ", current_tests_passed, current_tests);
    if (current_tests_passed == current_tests) {
        correct_modules++;
        printf("CORRECT");
    }
    else {
        printf("FAIL");
    }
    printf("\n");
}

void testPolynCmp_ZeroCase() {
    TestStart("zero case");
    struct Polynomial* p1 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p2 = ZeroPolynomial(CreateIntRing());
    rslt = polynCmp(p1, p2);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    TestEnd();
}
void testPolynCmp_ZeroAndNot() {
    TestStart("ZeroAndNot");
    int a[] = {1};
    struct Polynomial* p1 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p2 = polynCreator(a, 1, 1);
    rslt = !polynCmp(p1, p2);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    TestEnd();
}
void testPolynCmp_TwoDifferent() {
    TestStart("TwoDifferent");
    int a[] = {1, 2};
    int b[] = {2, 1};
    struct Polynomial* p1 = polynCreator(b, 2, 1);
    struct Polynomial* p2 = polynCreator(a, 2, 1);
    rslt = !polynCmp(p1, p2);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    TestEnd();
}
void testPolynCmp_TwoEqual() {
    TestStart("TwoEqual");
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    struct Polynomial* p1 = polynCreator(b, 3, 1);
    struct Polynomial* p2 = polynCreator(a, 3, 1);
    rslt = polynCmp(p1, p2);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    TestEnd();
}
void testPolynCmp_TwoDiffTypeFloat() {
    TestStart("TwoEqual");
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    struct Polynomial* p1 = polynCreator(b, 3, 1);
    struct Polynomial* p2 = polynCreator(a, 3, 1);
    rslt = polynCmp(p1, p2);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    TestEnd();
}


void test_polynCmp() {

    HeaderTestStart("polynomial compairing");
    testPolynCmp_ZeroCase();
    testPolynCmp_ZeroAndNot();
    testPolynCmp_TwoDifferent();
    testPolynCmp_TwoEqual();
    HeaderTestEnd();
}

void test_sum_ZeroZero() {
    TestStart("ZeroZero");
    struct Polynomial* p1 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p2 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p3 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p4 = sum(p1, p2);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}
void test_sum_ZeroAndNot() {
    TestStart("ZeroAndNot");
    double a[] = {1, 2, 3,5};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    struct Polynomial* p2 = polynCreator(NULL, 0, 2);
    struct Polynomial* p4 = sum(p1, p2);
    rslt = polynCmp(p4, p1);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p4);
    TestEnd();
}

void test_sum_TwoDifferent() {
    TestStart("TwoDifferent");
    int a[] = {1, 2, 3, 8, -1};
    int b[] = {-4, 5, 0};
    int c[] = {-3, 7, 3, 8, -1};
    struct Polynomial* p1 = polynCreator(a, 5, 1);
    struct Polynomial* p2 = polynCreator(b, 3, 1);
    struct Polynomial* p3 = sum(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 5, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}

void test_sum_TwoDifferent2() {
    TestStart("TwoDifferent2");
    int a[] = {1, 2, 3};
    int b[] = {-4, 5, 0, 8, 11};
    int c[] = {-3, 7, 3, 8, 11};
    struct Polynomial* p1 = polynCreator(a, 3, 1);
    struct Polynomial* p2 = polynCreator(b, 5, 1);
    struct Polynomial* p3 = sum(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 5, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}

void test_sum_TwoDifferentDouble() {
    TestStart("TwoDifferentDouble");
    double a[] = {1.2, 2.5, 3.77};
    double b[] = {-4.5, 5, 0, 8, 11};
    double c[] = {-3.3, 7.5, 3.77, 8, 11};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    struct Polynomial* p2 = polynCreator(b, 5, 2);
    struct Polynomial* p3 = sum(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 5, 2);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}


void test_sum() {

    HeaderTestStart("polynomial sum");
    test_sum_ZeroZero();
    test_sum_ZeroAndNot();
    test_sum_TwoDifferent();
    test_sum_TwoDifferent2();
    test_sum_TwoDifferentDouble();
    HeaderTestEnd();
}

void test_multScal_ZeroZero() {
    TestStart("TwoDifferentDouble");
    double *a = malloc(sizeof(double));
    *a = 0;
    struct Polynomial* p2 = polynCreator(NULL, 5, 2);
    struct Polynomial* p3 = polynCreator(NULL, 0, 2);
    struct Polynomial* p4 = multScal(p2, (void *)a);
    rslt = polynCmp(p2, p3);
    //DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    free(a);
    TestEnd();
}
void test_multScal_ZeroAndNot() {
    TestStart("TwoDifferentDouble");
    double *n = malloc(sizeof(double));
    *n = 2;
    double a[] = {1.2, 1.5, 3.55};
    double b[] = {2.4, 3, 7.1};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    struct Polynomial* p2 = multScal(p1, n);
    struct Polynomial* p3 = polynCreator(b, 3, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}

void test_multScal_TwoDifferent() {
    TestStart("Not zero polyn and zero number");
    double *n = malloc(sizeof(double));
    *n = 0;
    double a[] = {1.2, 1.5, 3.55};
    double b[] = {3.6, 3, 7.1};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    struct Polynomial* p2 = multScal(p1, n);
    struct Polynomial* p3 = polynCreator(NULL, 3, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}

void test_multScal_TwoDifferent2() {
    TestStart("Zero polyn and not zero number");
    double *n = malloc(sizeof(double));
    *n = 5;
    double a[] = {1.2, 1.5, 3.55};
    double b[] = {3.6, 3, 7.1};
    struct Polynomial* p1 = polynCreator(NULL, 3, 2);
    struct Polynomial* p2 = multScal(p1, n);
    struct Polynomial* p3 = polynCreator(NULL, 3, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}
void test_multScal_TwoDifferent3() {
    TestStart("multiply by negative");
    double *n = malloc(sizeof(double));
    *n = -5;
    double a[] = {1.2, -1.5, 3.25};
    double b[] = {-6, 7.5, -16.25};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    struct Polynomial* p2 = multScal(p1, n);
    struct Polynomial* p3 = polynCreator(b, 3, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}

void test_multScal() {

    HeaderTestStart("mult scal");
    test_multScal_ZeroZero();
    test_multScal_ZeroAndNot();
    test_multScal_TwoDifferent();
    test_multScal_TwoDifferent2();
    test_multScal_TwoDifferent3();
    HeaderTestEnd();
}

void test_mult_int() {
    TestStart("mult int");
    int a[] = {1, -2, 3};
    int b[] = {-4, 5, 0, 8, 11};
    int c[] = {-4, 13, -22, 23, -5, 2, 33};
    struct Polynomial* p1 = polynCreator(a, 3, 1);
    struct Polynomial* p2 = polynCreator(b, 5, 1);
    struct Polynomial* p3 = mult(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 7, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}
void test_mult_double() {
    TestStart("mult_double");
    double a[] = {1, -1.5};
    double b[] = {-1, 0, 0.5};
    double c[] = {-1, 1.5, 0.5, -0.75};
    struct Polynomial* p1 = polynCreator(a, 2, 2);
    struct Polynomial* p2 = polynCreator(b, 3, 2);
    struct Polynomial* p3 = mult(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 4, 2);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}
void test_mult_ZeroAndNot() {
    TestStart("ZeroAndNot");
    double a[] = {1, -1.5};
    double b[] = {-1, 0, 0.5};
    double c[] = {-1, 1.5, 0.5, -0.75};
    struct Polynomial* p1 = polynCreator(a, 2, 2);
    struct Polynomial* p2 = polynCreator(NULL, 3, 2);
    struct Polynomial* p3 = mult(p1, p2);
    struct Polynomial* p4 = polynCreator(NULL, 4, 2);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}

void test_mult_ZeroZero() {
    TestStart("ZeroZero");
    double a[] = {1, -1.5};
    double b[] = {-1, 0, 0.5};
    double c[] = {-1, 1.5, 0.5, -0.75};
    struct Polynomial* p1 = polynCreator(NULL, 0, 2);
    struct Polynomial* p2 = polynCreator(NULL, 0, 2);
    struct Polynomial* p3 = mult(p1, p2);
    struct Polynomial* p4 = polynCreator(NULL, 0, 2);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}

void test_mult_One() {
    TestStart("mult_One");
    double a[] = {1};
    double b[] = {-1, 0, 0.5};
    double c[] = {-1, 1.5, 0.5, -0.75};
    struct Polynomial* p1 = polynCreator(a, 1, 2);
    struct Polynomial* p2 = polynCreator(b, 3, 2);
    struct Polynomial* p3 = mult(p1, p2);
    struct Polynomial* p4 = polynCreator(b, 3, 2);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}


void test_mult() {

    HeaderTestStart("multiplication");
    test_mult_ZeroZero();
    test_mult_ZeroAndNot();
    test_mult_One();
    test_mult_int();
    test_mult_double();
    HeaderTestEnd();
}


void test_calculation_ZeroZero() {
    TestStart("test_calculation_ZeroZero");
    double *a = malloc(sizeof(double));
    *a = 0;
    struct Polynomial* p1 = polynCreator(NULL, 5, 2);
    rslt = (*(double *)calculation(p1, (void*)a) == 0);
    DeletePolynomial(p1);
    free(a);
    TestEnd();
}
void test_calculation_Zero() {
    TestStart("test_calculation_Zero");
    double *a = malloc(sizeof(double));
    *a = 5;
    struct Polynomial* p1 = polynCreator(NULL, 5, 2);
    rslt = (*(double *)calculation(p1, (void*)a) == 0);
    DeletePolynomial(p1);
    free(a);
    TestEnd();
}
void test_calculation_ZeroNumber() {
    TestStart("test_calculation_ZeroNumber");
    double *n = malloc(sizeof(double));
    *n = 0;
    double a[] = {1.2, 1.5, 3.55};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    rslt = (*(double *)calculation(p1, (void*)n) == 0);
    DeletePolynomial(p1);
    free(n);
    TestEnd();
}
void test_calculation_One() {
    TestStart("test_calculation_One");
    double *n = malloc(sizeof(double));
    *n = 1;
    double a[] = {2.5, 1.5, 3.55};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    rslt = (*(double *)calculation(p1, (void*)n) == 7.55);
    DeletePolynomial(p1);
    free(n);
    TestEnd();
}


void test_calculation_double() {
    TestStart("test_calculation_double");
    double *n = malloc(sizeof(double));
    *n = 3.5;
    double a[] = {2.5, 1.5, 3.55};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    rslt = (*(double *)calculation(p1, (void*)n) == 173.08124999999998);
    DeletePolynomial(p1);
    free(n);
    TestEnd();
}

void test_calculation_int() {
    TestStart("test_calculation_int");
    int *n = malloc(sizeof(int));
    *n = 6;
    int a[] = {2, -4, -3};
    struct Polynomial* p1 = polynCreator(a, 3, 1);
    rslt = (*(int *)calculation(p1, (void*)n) == -790);
    DeletePolynomial(p1);
    free(n);
    TestEnd();
}


void test_calculation() {

    HeaderTestStart("calculation");
    test_calculation_Zero();
    test_calculation_ZeroZero();
    test_calculation_ZeroNumber();
    test_calculation_One();
    test_calculation_int();
    test_calculation_double();
    HeaderTestEnd();
}

void test_spas_ZeroZero() {
    TestStart("sumZeroPolynAndZeroScal");
    double *a = malloc(sizeof(double));
    *a = 0;
    struct Polynomial* p2 = polynCreator(NULL, 5, 2);
    struct Polynomial* p3 = polynCreator(NULL, 0, 2);
    struct Polynomial* p4 = sumPolynAndScal(p2, (void *)a);
    rslt = polynCmp(p2, p3);
    //DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    free(a);
    TestEnd();
}
void test_spas_ZeroAndNot() {
    TestStart("Not zero polyn and zero number");
    double *n = malloc(sizeof(double));
    *n = 0;
    double a[] = {1.2, 1.5, 3.55};
    double b[] = {2.4, 3, 7.1};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    struct Polynomial* p2 = sumPolynAndScal(p1, n);
    struct Polynomial* p3 = polynCreator(a, 3, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}

void test_spas_TwoDifferent() {
    TestStart("test_sumPolynAndScal_ZeroAndNot");
    double *n = malloc(sizeof(double));
    *n = 5;
    double a[] = {5};
    double b[] = {3.6, 3, 7.1};
    struct Polynomial* p1 = polynCreator(NULL, 3, 2);
    struct Polynomial* p2 = sumPolynAndScal(p1, n);
    struct Polynomial* p3 = polynCreator(a, 1, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}

void test_spas_TwoDifferent2() {
    TestStart("Zero polyn and not zero number");
    double *n = malloc(sizeof(double));
    *n = 5;
    double a[] = {1.2, 1.5, 3.55};
    double b[] = {6.2, 1.5, 3.55};
    struct Polynomial* p1 = polynCreator(a, 3, 2);
    struct Polynomial* p2 = sumPolynAndScal(p1, n);
    struct Polynomial* p3 = polynCreator(b, 3, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}
void test_spas_TwoDifferent3() {
    TestStart("multiply by negative");
    double *n = malloc(sizeof(double));
    *n = -5;
    double a[] = {1.2};
    double b[] = {-3.8};
    struct Polynomial* p1 = polynCreator(a, 1, 2);
    struct Polynomial* p2 = sumPolynAndScal(p1, n);
    struct Polynomial* p3 = polynCreator(b, 1, 2);
    rslt = polynCmp(p2, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    free(n);
    TestEnd();
}

void test_sumPolynAndScal() {

    HeaderTestStart("sumPolynAndScal");
    test_spas_ZeroZero();
    test_spas_ZeroAndNot();
    test_spas_TwoDifferent();
    test_spas_TwoDifferent2();
    test_spas_TwoDifferent3();
    HeaderTestEnd();
}


void test_composition_int() {
    TestStart("test_composition_int");
    int a[] = {7, 1};
    int b[] = {-5, 4, 1};
    int c[] = {72, 18, 1};
    struct Polynomial* p1 = polynCreator(b, 3, 1);
    struct Polynomial* p2 = polynCreator(a, 2, 1);
    struct Polynomial* p3 = composition(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 3, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}

void test_composition_Zero() {
    TestStart("test_composition_Zero");
    int b[] = {-5, 4, 1};
    int c[] = {-5};
    struct Polynomial* p1 = polynCreator(b, 3, 1);
    struct Polynomial* p2 = polynCreator(NULL, 2, 1);
    struct Polynomial* p3 = composition(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 1, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}
void test_composition_ZeroAndNot() {
    TestStart("test_composition_ZeroAndNot");
    int b[] = {-5, 4, 1};
    struct Polynomial* p1 = polynCreator(b, 3, 1);
    struct Polynomial* p2 = polynCreator(NULL, 2, 1);
    struct Polynomial* p3 = composition(p2, p1);
    struct Polynomial* p4 = polynCreator(NULL, 1, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}
void test_composition_ZeroZero() {
    TestStart("test_composition_ZeroZero");
    struct Polynomial* p1 = polynCreator(NULL, 3, 1);
    struct Polynomial* p2 = polynCreator(NULL, 2, 1);
    struct Polynomial* p3 = composition(p1, p2);
    struct Polynomial* p4 = polynCreator(NULL, 3, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}
void test_composition_one() {
    TestStart("test_composition_one");
    int a[] = {10, -7, 1};
    int b[] = {1};
    int c[] = {4};
    struct Polynomial* p1 = polynCreator(a, 3, 1);
    struct Polynomial* p2 = polynCreator(b, 1, 1);
    struct Polynomial* p3 = composition(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 1, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}
void test_composition_one2() {
    TestStart("test_composition_one2");
    int a[] = {10, -7, 1};
    int b[] = {0, 1};
    int c[] = {10, -7, 1};
    struct Polynomial* p1 = polynCreator(a, 3, 1);
    struct Polynomial* p2 = polynCreator(b, 2, 1);
    struct Polynomial* p3 = composition(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 3, 1);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}


void test_composition_double() {
    TestStart("test_composition_double");
    double a[] = {1, 0, 1.5};
    double b[] = {2.5, -1, 1};
    double c[] = {2.5, 0, 1.5, 0, 2.25};
    struct Polynomial* p1 = polynCreator(b, 3, 2);
    struct Polynomial* p2 = polynCreator(a, 3, 2);
    struct Polynomial* p3 = composition(p1, p2);
    struct Polynomial* p4 = polynCreator(c, 5, 2);
    rslt = polynCmp(p4, p3);
    DeletePolynomial(p1);
    DeletePolynomial(p2);
    DeletePolynomial(p3);
    DeletePolynomial(p4);
    TestEnd();
}

void test_composition() {

    HeaderTestStart("composition");
    test_composition_Zero();
    test_composition_ZeroAndNot();
    test_composition_ZeroZero();
    test_composition_one();
    test_composition_one2();
    test_composition_int();
    test_composition_double();
    HeaderTestEnd();
}

int main() {
    num_tests = 0;
    tests_passed = 0;
    num_modules = 0;
    correct_modules = 0;
    test_polynCmp();
    test_sum();
    test_multScal();
    test_mult();
    test_sumPolynAndScal();
    test_composition();

    printf("\nTotal correct modules: %d / %d\nTotal tests passed: %d / %d\n", correct_modules, num_modules, tests_passed, num_tests);

    return !(tests_passed == num_tests);
}
