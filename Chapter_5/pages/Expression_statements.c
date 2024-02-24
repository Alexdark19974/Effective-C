#include <stdio.h>
#include <stdlib.h>

/* Chapter 5: Control Flow
    Subchapter: Expression Statements and Compound Statements
   Pages: 81 - 82 */

int main(void)
{
    /* Expression statements with initializers */
    int a;
    int b = 1;
    int c = 0;
    int count = 0;

    /* Between an each expression statement,
       There is a sequence point
       So that all side effects are produces
       Before executing the next line of code */

    a = 6; // assignment is a side effect too
    c = a + b; // a side effect is the updated value
    ; // null statement, does nothing
    ++count; // a side effect of prefix increment is the change of state of count (updated value)

    /* Compound statement or a block */
    /* Allow to execute substatement sequentially */
    /* Scope rules DO apply */
    {
        ; // substatement that does nothing
        static int count = 0; // block-scope declaration/definition of static count
        c += a; // c and a have a scope of main function
        ++count;
        printf("Static count inside a compound statement = %d\n", count);

        /* Nested compound statement */
        {
            static int count = 0; // block scope
            printf("Static count inside a nested compound statement = %d\n", count);
        }
    }
    printf("Count inside a compound statement of function block-scope main = %d\n", count);

    return EXIT_SUCCESS;
}

