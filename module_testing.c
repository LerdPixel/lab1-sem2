#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "for_testing.h"

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

    TestEnd();
}
void testPolynCmp_ZeroAndNot() {
    TestStart("ZeroAndNot");
    int a[] = {1};
    struct Polynomial* p1 = ZeroPolynomial(CreateIntRing());
    struct Polynomial* p2 = polynCreator(a, 1, 1);
    rslt = !polynCmp(p1, p2);

    TestEnd();
}
void testPolynCmp_TwoDifferent() {
    TestStart("TwoDifferent");
    int a[] = {1, 2};
    int b[] = {2, 1};
    struct Polynomial* p1 = polynCreator(b, 2, 1);
    struct Polynomial* p2 = polynCreator(a, 2, 1);
    rslt = !polynCmp(p1, p2);

    TestEnd();
}
void testPolynCmp_TwoEqual() {
    TestStart("TwoEqual");
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    struct Polynomial* p1 = polynCreator(b, 3, 1);
    struct Polynomial* p2 = polynCreator(a, 3, 1);
    rslt = polynCmp(p1, p2);

    TestEnd();
}
void testPolynCmp_TwoDiffTypeFloat() {
    TestStart("TwoEqual");
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    struct Polynomial* p1 = polynCreator(b, 3, 1);
    struct Polynomial* p2 = polynCreator(a, 3, 1);
    rslt = polynCmp(p1, p2);

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

int main()
{
    num_tests = 0;
    tests_passed = 0;
    num_modules = 0;
    correct_modules = 0;
    test_polynCmp();
    printf("\nTotal correct modules: %d / %d\nTotal tests passed: %d / %d\n", correct_modules, num_modules, tests_passed, num_tests);

    return !(tests_passed == num_tests);
}
