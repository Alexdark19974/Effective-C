#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

/* Fix the remaining bug in the absolute_value function in Listing 5-14 */

int absolute_value(int a)
{
    return a == INT_MIN || a >= 0 ? a: -a; // check for INT_MIN to prevent integer overflow
}

int main(void)
{
    int a = INT_MIN;
    printf(" absolute value of %d is %d\n", a, absolute_value(a));

    return EXIT_SUCCESS;
}

