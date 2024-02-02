#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 
    Chapter 4: Expressions and Operators
        Subchapter: Relational Operators
    Page: 77
*/

int main(void)
{
    int i = 0, j = 0, a = 5, b = 6, c = 7;

    /* 
     * 2 objects have different addresses in memory space;
     * Relational operators can used for arithmetic types and pointers
     * Take caution when using "< > <= >=" when applied to pointers
     * They may lead to undefined behavior for pointers
     * '==' or '!=' stand out as safe in comparisions
     * But double-check your logic befor applying them to pointers
     * */
    {
        bool b1 = &i < &j;  // undefined behavior
        printf("%u\n", b1);

        bool b2 = &i == &j; // okay, but tautologically false

        printf("%u\n", b2);

        bool *b1p = &b1;
        bool *b2p = &b1;

        /* b1p and b2p contain an identical address */
        b2 = b1p == b2p; // shall return 1
        printf("%u\n", b2);
    }

    {
        int ret = 0;

        /* This generates a warning (-Wparentheses) 
         * Writing (a < b) == (b < c) improves readability */
        ret = a < b == b < c; // equals to ret = (a < b) == (b < c) -> ret = 1/0 == 1/0 -> ret = 1/0
        
        printf("ret = %u\n", ret);
    }

    return EXIT_SUCCESS;
}
