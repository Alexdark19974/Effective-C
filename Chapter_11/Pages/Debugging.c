#define _STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>

/* Chapter 11: Debugging, Testing, and Analysis
    Subchapter: Debugging
   Pages: 208 - 211 */

/* Compile with -Og -g3 to obtain the debugging information
 * And debug with gdb to explore the code */

/*errno_t*/ int print_error(/*errno_t */ int errnum)
{
    /*rsize_t*/ size_t size = errnum + 124 /* strerrorlen_s(errnum) */;
    char *msg = malloc(size);
    /* strerror_s (this is relevant to C11 for Microsoft) is not supported by my implenetation */
    /* Neither is strerror_s, although it should be. */

    /* The erroneous part is the return value of strerror_s is 0 upon SUCCESS */
#if 0
    if ((msg != NULL) && (strerror_r(errnum, msg, size) /*strerror_s(msg, size, errnum)*/ != 0)) {
        fputs(msg, stderr);
        free(msg); // another bug of the program is free() missing
        return 0;
    }
#endif
    /* The return value is as it should be */
    if (msg != NULL) {
        int error = strerror_r(errnum, msg, size);
        if (error == 0)
            fputs(msg, stderr);
        else
            perror("strerror_r");
        free(msg); // another bug of the program is free() missing
        return ENOMEM;
    }
    else {
        fputs("unknown error\n", stderr);
        if (errno != 0) // additional error checking
            perror("strerror_r");
        return ENOMEM;
    }
}

int main(void) {
    print_error(ENOMEM);
    exit(1);
}

