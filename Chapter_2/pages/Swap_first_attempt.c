#include <stdio.h>

/* Chapter 2: Object, Functions, and Types
    Subchapter: Swapping Values (First Attempt)
   Pages: 15 - 16 */

void swap(int, int); // declared but not defined

int main(void)
{
    /* Local variables have automatic storage duration
       They exist until execution leaves the block
       Where they are defined
       Local variables have a lifetime of block */
    int a = 21;
    int b = 17;

    /* Values of a and b objects will be swapped exclusively inside swap() function
       Because values of a, b passed in main() as arguments are copied to swap() parameters as values
       a,b in main() and a,b in swap() are distinct and have different locations in memory
       This is call-by-value or pass-by-value. */
    swap(a, b); // arguments
    printf("main: a = %d, b = %d\n", a, b);
    return 0;
}

void swap(int a, int b) // parameters declared as part of function declaration (on the top)
{
    int t = a;
    a = b;
    b = t;
    printf("swap: a = %d, b = %d\n", a, b);
}

