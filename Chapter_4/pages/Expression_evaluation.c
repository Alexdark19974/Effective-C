#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Simple Assignment
    Page: 58
*/

void usage_of_rvalue_lvalue(void)
{
    int i;
    i = 5;      // i is an lvalue, 5 is an rvalue
    int j = i;  // lvalues can appear on the right-hand side of an assignment
    // 7 = i;      // error: rvalues can't appear on the left-hand side of an assignment
}

void show_assignment_constraints(void)
{
    signed char c;
    int i = INT_MAX;
    long k;
    /*
     * 1) c has signed char type, but i has signed int so value of INT_MAX is truncated to allow for value that c can hold; value greater than SCHAR_MAX are truncated
     * 2) 1 1 1 1 1 1 1 1 == -1, previously 2147483647 (0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
     * 3) the rvalue of the assignment operator is converted to the type of the lvalue (signed long int)
     * */
    k = (c = i); // value of i is assigned to c, then assigned to k
    printf("k = %ld\n", k);
}

int main(void)
{
    /*
     * 1) i = 21; i - lvalue, 21 - rvalue;
     * rvalue is converted to the type of object, the value of which lvalue stores (int)
     * 2) i = j; lvalues can be to the left or right of the assignment expression
     * */

    int i = 21; // declaration with initializer
    int j = 7;  // declaration with initializer
    i = j;      // simple assignment of rvalue to lvalue


    /*
     * 1) i is lvalue that is converted to rvalue;
     * 2) the sum of i + 12 is the rvalue assigned to the left operand (j)
     * 3  the rvalue can be just a number (12);
     */
    j = i + 12; // j now has the value 19
    

    usage_of_rvalue_lvalue();
    show_assignment_constraints();
#if 0
    int i = 5;
    int j = 6;
    int k = 7;

    /* We can be sure of several things in the following expression:
     * 1) i, j, k must be evaluated before any operations take place
     * 2) Multiplication has higher precedence, we do it first
     * 3) Before that, we need to resolve all side effects resulting from prefix increment of j and k
     * 4) the order of what gets incremented first and what gets evaluated in the 1st place is unspecified
     * 5) i must be evaluated and its side effects resolved before operation + takes place 
     * 6) We cannot know what identifier gets evaluated first since the order of eval is unspecified */

    printf("%d\n", ++i + ++j * k); // okay, but implies indeterminately sequential evaluations

    /* do NOT do more than 1 read/wrtie to the same object per expression using the sambe object
     * If it implies side effects */
    
    /* undefined behavior */
    i = ++i; // it will generate warning about unsequenced modificaition of the same object
    printf("i = %d\n", i);
    i = i + j + i++; // the same undefined behavior
    printf("i = %d\n", i);
#endif
    return EXIT_SUCCESS;
}
