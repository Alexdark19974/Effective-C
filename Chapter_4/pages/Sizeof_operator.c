#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

/* Chapter 4: Expressions and Operators
    Subchapter: sizeof Operator
   Page: 67 */

int main(void)
{
    int i;
    size_t i_size = sizeof i;       // the size of the object i
    size_t int_size = sizeof(int);  // the size of the type int
    int arr[100] = {1 ,2, 3, 4, 5};
    // sizeof operator does not evaluate operands passed to it
    printf("available bits of i_size = %lu\n", CHAR_BIT * sizeof i); // unevaluated complete object types need not be parenthesized
    printf("available bits of int_size = %lu\n", CHAR_BIT * sizeof(int)); // Name of type must be parenthesized

    i = 0;
    // But sometimes, it does.
    printf("sizeof of %d element of arr is %lu\n", i, sizeof(arr[i++])); // produces a warning
    printf("i is %d\n", i); // will remain zero because operands passed to sizeof are not evaluated (except for variable-length arrays)

    printf("%lu\n", sizeof(int[i++])); // i will be incremented since the size of variable-length array is calculated here.
    printf("%d\n", i);

    return EXIT_SUCCESS;
}

