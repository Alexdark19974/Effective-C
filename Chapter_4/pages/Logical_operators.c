#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Chapter 4 Expressions and Operators
        Subchapter: Logial Operators
    Page: 73
*/

bool isN(int *ptr, int n);
bool is_file_ready(void);
bool prepare_file();

int main(void)
{
    /* Evaluation for "&&" and "||" is guaranteed to be left to right
       Expressions with operators return either 1 or 0
       Both operators short-circuit:
       If the 1st operand of || is true, expressions is true, || returns 1
       If th1 1st operand of && is false, expressions is false, && returns 0 */
    int *ptr = NULL;
    int ret = 0;

    {
        ret = isN(ptr, 20);

        printf("isN = %u\n", ret);

        ret = 20, ptr = &ret, ret = isN(ptr, 20);

        printf("isN = %u\n", ret);
    }

    {
        /* If left operand is 1, the expression short-circuits and doesn't evalue the right operand
           if it is 0, the right operand is evaluated
           if both are 0, the subexpression in if-statement is not executed; */
        if (is_file_ready() || prepare_file()) goto enough;
    }

    {
        enum { max = 15 };
        int i = 17;

        /* Be careful when there are side effects in the second operand of &&
           Is this what you really wanted? */
        if ( (i >= 0) &&  ( (i++) <= max) )  { // could be written as (i >= 0 && i++ <= max) but not as easy to read
            puts("Something happened");
        }

    }

enough:
    return EXIT_SUCCESS;
}


bool isN(int *ptr, int n)
{
    /* short-circuit: returns 0 (false) if ptr ==-NULL */
    return ptr && *ptr  == n; // don't dereference a null pointer
}

bool is_file_ready(void)
{
    return true;
}

bool prepare_file(void)
{
    return true;
}

