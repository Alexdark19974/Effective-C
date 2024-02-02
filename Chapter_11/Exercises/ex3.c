#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "unity.h"

/* So far, the code here has memory leaks and inconsistency in Unit testing */
/*
	Static analysis:
	1) there's no free() in both get_error() and print_error() when we allocate memory;
	2) TEST_ASSERT_EQUAL_INT(print_error(), 0); tests for 0 zero, although the function returns errno passed to it
	Dynamic analysis:
	1) Valgrind caught memory leaks;
	2) AddressSanitizer caught memory leaks
*/

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

/* strerror_s is only available for C11/Windows 
	as well as many typedefs presented in the book */
char *get_error(int errnum) {
	size_t size = 128;
	char *msg = malloc(size);
	if (msg != NULL) {
		char *err = strerror(errnum);
		if (err == NULL) {
			strncpy(msg, "unknown error", size - 1);
			msg[size - 1] = '\0';
		} else {
			strncpy(msg, err, size - 1);
			msg[size - 1] = '\0';
		}
	}
	return msg;
}

int print_error(int errnum)
{
	size_t size = 128;
	char *msg = malloc(size);
	if (msg != NULL) {
		char *err = strerror(errnum);
		if (err != NULL) {
			strncpy(msg, err, size - 1);
			msg[size - 1] = '\0';

			fputs(msg, stderr);
			fputc('\n', stderr);
			free(msg); // added to avoid memory leak
			return 0/* ENOMEM */;
		}
		else {
			fputs("unknown error", stderr);
			fputc('\n', stderr);
			free(msg); // added to avoid memory leak
			return 0/* ENOMEM */;		
		}
	}
	else {
		fputs("unknown error", stderr);
		fputc('\n', stderr);
		return 0/* ENOMEM */;		
	}
}

void test_suite1(void)
{
	char *retp = NULL;

	TEST_ASSERT_EQUAL_STRING((retp = get_error(ENOMEM)), /* Not enough memory*/ "Cannot allocate memory");
	free(retp); // added to avoid memory leak
	TEST_ASSERT_EQUAL_STRING((retp = get_error(ENOTSOCK)), /*"Not a socket"*/ "Socket operation on non-socket");
	free(retp); // added to avoid memory leak
	TEST_ASSERT_EQUAL_STRING((retp = get_error(EPIPE)), "Broken pipe");
	free(retp); // added to avoid memory leak

	TEST_ASSERT_EQUAL_INT(print_error(ENOMEM), 0);
	TEST_ASSERT_EQUAL_INT(print_error(ENOTSOCK), 0);
	TEST_ASSERT_EQUAL_INT(print_error(EPIPE), 0);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_suite1);
	return UNITY_END();
}
