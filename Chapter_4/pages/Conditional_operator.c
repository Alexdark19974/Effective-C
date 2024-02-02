#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) (a < b) ? b : a // (a < b) is evaluated first, then either b or a

/*
    Chapter 4: Expressions and Operators
        Subchapter: Conditional Operator
    Page: 76
*/

int main(void)
{
    int a = 5, b = 6;

    /* the return type is of the second or third operand */
    const int x = MAX(a,b); // conditional operator can be used to initialize const qualified object

    printf("MAX is %d\n", x);

    return EXIT_SUCCESS;
}
