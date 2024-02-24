#include <stdio.h>
#include <stdlib.h>

/* Chapter 4 Expressions and Operators
    Subchapter: Compound Assignment Operators
   Page: 78 */

int main(void)
{
    int i = 5, j = 6;
    int c = 7;

    i *= j - c; // -5 or 23 ?

   printf("i = %d\n", i); // -5

   /* '*=' operator has lower precedence than '-' operator
      It will look like this:
      i *= (j - c);
      i = i * j - c shall yield a different result; */

    return EXIT_SUCCESS;
}

