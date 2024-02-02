#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Increment and Decrement Operators
    Page: 61
*/

int main(void)
{
    /* Both increment and decrement operators increment/decrement lvalue by 1 */
    int i = 5;
    int e;      // result of the expression
    /* Postfix increment returns the original value first, then increments updating the value as a side effect */
    e = i++;    // postfix increment: i has the value 6; e has the value 5
    e = i--;    // postfix decrement: i has the value 5; e has the value 6
    /* Prefix increment increments first updating the value as a side effect, then returns the value */
    e = ++i;    // prefix increment: i has the value 6; e has the value 6
    e = --i;    // prefix decrement: i has the value 5; e has the value 5

     return EXIT_SUCCESS;
}
