#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 1: Getting Started With C
        Subchapter: Checking Function Return Values
    Pages: 5 - 12
*/

int main(void) 
{
    if (puts("Hello, world!") == EOF) {
        return EXIT_FAILURE;
        // code here never executes
    }

    return EXIT_SUCCESS;
    // code here never executes
}

/* Although very unlikely, puts may return EOF which
 * inidicates a failure to write/output "Hello, World to stdout
 * and may mean a failure of a console/terminal "*/

#if 0

int main(void) 
{
    /* returning a negative integer value upon failure 
        does not  necessarily mean that if is equal to EOF (-1)
        because negative integer value does not equal to EOF (-1)
        unless explicitly stated in documentation */
 
    if (printf("Hello, world!\n") < 0) {
        return EXIT_SUCCESS;
    }

    // printf("%s\n", "Hello, world"); // is this version better than the one above ?
    /* if (puts("Hello, world!") == EOF) {
        return EXIT_FAILURE;
        // code here never executes
    } */

    return EXIT_SUCCESS;
    // code here never executes
}

/* Although very unlikely, puts may return EOF which
 * inidicates a failure to write/output "Hello, World to stdout
 * and may mean a failure of a console/terminal "*/

#endif