#include <stdio.h>
#include <stdlib.h>

/* Chapter 4: Expressions and Operators
    Subchapter: Comma Operator
   Page: 78 */

void do_something(int a, int b, int c); // comma as a separator

int main(void)
{
    int i = 5, j = 6; // comma as a separator
    int c = 7;

    /* evaluate i, then increment it, then evaluate j, then decrement it */
    i++, j--; // comma as an operator

    c = i, j; // j is discarded
    printf("c = %d\n", c);

    /* parentheses force i and j to be evaluated first */
    c = (i, j); // return value of comma operator is the right-most operand
    printf("c = %d\n", c);

    do_something(i, j, c); // comma as a separator
    do_something(i, (j = 0, ++j), (c = i, c++)); // a comma operator works inside the list if () operator is used
    return EXIT_SUCCESS;
}

void do_something(int a, int b, int c)
{
    ;
}

