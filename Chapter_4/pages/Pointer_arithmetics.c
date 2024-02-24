#include <stdio.h>
#include <stdlib.h>

/* Chapter 4: Expressions and Operators
    Subchapter: Pointer Arithmetic
   Page: 79 */

int sum_m_elemns(void)
{
    int m[2] = {1, 2};
    int *pi; int j = 0;

    /* &m[2] is too-far a pointer to an too-far object */
    for (pi = &m[0]; pi < &m[2]; ++pi) j += *pi;
    /* j += *pi --> compound assignment operator (j evaluated once)
     * j += *pi == j = j + (*pi); */

    return j;
}

int main(void)
{
    int arr[100] = {0};
    int *arrp1 = &arr[40]; // address of 40-th element of arr[100]
    int *arrp2 = arrp1 + 20; // arrp1 + (20 * sizeo(int))

    printf("ptrdiff = %td\n", arrp2 - arrp1);

    printf("sum = %d\n", sum_m_elemns());

    return EXIT_SUCCESS;
}

