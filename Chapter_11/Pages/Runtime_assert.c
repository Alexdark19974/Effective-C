#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define _XOPEN_SOURCE 700
#define LIMIT 124

/* Chapter 11: Debugging, Testing, and Analysis
    Subchapter: Assertions:
        1) Runtime assertions;
    Pages: 202 - 203 */


int main(void)
{
    /* assert, unlike static_assert, performes diagnostics during runtime */
    /* #define assert(scalar-expression) > implementation definted */
    /* If the expression is evaluated to 0, then contents of argument is
        Written to stderr:
        1) the expression iself;
        2), __func__, __FILE__, __LINE__ are also added to the output
    Then abort() is called. */

    void *dup_string(size_t size, char *str);

    char *str = "random data";
    char *copied_str = dup_string(strlen(str) + 1, str);

    if (copied_str == NULL) {
        fprintf(stderr, "error: failed to copy string.\n");
        return EXIT_FAILURE;

    }

    /* You should disable asssertions before code is deployed by defining the NDEBUG macro
    as a flag -DNDEBUG=1 to the compiler */

    /* As soon as NDEBUG is defined, macro assert() looks like this:
        #define assert(ignore) ((void)0) */
    /* Casting 0 to void allows us to avoid compiler warnings */
    0;  // produces a compile warning
    ((void ) 0); // supresses a compile warning
    /* Of coutse, we need statement operator ";" for anything to work */

    /*  We do not add ";" in macros to avoid syntax errors and to allow a user to add it themselves
        Thus emulating a function. Follow: https://stackoverflow.com/questions/61157541/c-macros-whats-the-meaning-of-void0 */
    /*
        if (1)          if (1)
            ASSERT(); >     replacementlist;; -> syntax error
        else            else
          ;                 ; */

    /* Use static_asssert() to verify assumptions about code flow at compile time */

    /* Use runtime assert() to verify assumptions about code while testing the program */

    /* In the code to be deployed, assertions must be turned off, thus you have to provide
        for normal condition checking such as the following:
        1) Invalid output;
        2) Errors opening, reading, or writing streams;
        3) Out-of-memory conditions from dynamic allocation functions;
        4) Syscall call errors;
        5) Invalid permissions;
        Assertions are a tool, not a be-all-and-all solution, only suitable for testing and debugging purposes. */
    return EXIT_SUCCESS;
}

void *dup_string(size_t size, char *str)
{
    /* during testing, we assume that the caller passed a NON-null string with correct size */
    /* assert() verifies this assumption. */
    assert(size <= LIMIT && "size is larger then the expected limit"); // size is more than LIMIT, display a diagnostic
    /* Using && and additional text message is valid for assert() */
    /* The argument passed to assert() is stringified into a string literal */
    assert(str != NULL);

    void *data = (void *) strndup(str, size);

    return data;
}

