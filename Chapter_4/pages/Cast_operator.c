#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Chapter 4: Expressions and Operators
    Subchapter: Cast Operators
   Page: 75 */

int main(void)
{
    /* cast operators are used to explicitly cast from one type to another; loss of data is possible upon casting to smaller types : int > char, etc. */

    double x = 1.2;
    /* we lose 0.2 in precision */
    int sum = (int) x + 1; // without cast operator, the value would be implicitly converted to the type left of assignment operaor;
    printf("sum = %d\n", sum);

    return EXIT_SUCCESS;
}

