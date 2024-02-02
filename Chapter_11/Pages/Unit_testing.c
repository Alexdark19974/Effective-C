#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include "unity.h"

/*
    Chapter 11: Debugging, Testing, and Analysis
        Subchapter: Unit Testing
    Pages: 211 - 214
*/

void setUp(void) {
    printf("\n UNIT TEST BEGIN\n");
    // set stuff up here
}

void tearDown(void) {
    printf("\n UNIT TEST END\n");
    // clean stuff up here
}

char *print_error(int errnum) {

        TEST_ASSERT_FALSE(errnum <= 0);

        char *error = strerror(errnum);

        TEST_ASSERT_NOT_NULL(error);

        return error;
}


int increment_to_100(void) {
    int i;

    for (i = 0; i < 100; i++) ;

    return i;
}

/* testing environment */
void test_func(void) {
    /* a suite of test cases */
    // TEST_ASSERT_EQUAL_STRING(print_error(ENOMEM), "Out of memory");
    TEST_ASSERT_EQUAL_STRING(print_error(ENOMEM), "Cannot allocate memory");
    TEST_ASSERT_EQUAL_INT(increment_to_100(), 100);
}


int main(void) {

    /* Unit tests exercise separate units of your program which are usually
       Functions or data abstractions */

    /* We need unity testing to make sure program units behave in an expected
       way, i.e. it does what it's supposed to do */

    /* In order to implement unit testing, we will use framework "Unity" for
       C language to avoid C++ and Visual C++ */

    /* Unity provides for function-like macro and other macros resembling
       assertions (static_assert() and assert()). Basically, it's a
       collection of assertions wrapped in some code. */

    /* The only downside is that it doesn't provide for nonfatal macros. */

    UNITY_BEGIN(); // initialize unity framework

    RUN_TEST(test_func, __LINE__); // RUN_TEST macro launches testing

    return UNITY_END();
}
