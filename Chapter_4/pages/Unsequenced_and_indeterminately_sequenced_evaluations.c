#include <stdio.h>
#include <stdlib.h>

/* Chapter 4: Expressions and Operators
    Subchapter: Unsequenced and Indeterminately Sequenced Evaluations
   Page: 64 */

int main(void)
{
    /* Indeterminately sequenced Evaluations:
        1) Do not interleave;
        2) May happen in any order (taking into account operator precedence and assosciativity);
        3) Do not cause UB; */
    int i = 0;
    int j = 0;
    int k = 2;

    /* We can be sure of several things in the following expression:
        1) i, j, k must be evaluated before any operations take place
        2) Then we need to resolve all side effects resulting from prefix increment of j and k;
        3) Multiplication has higher precedence, we do it first
        4) the order of what gets incremented first and what gets evaluated in the 1st place is unspecified in a subexpression such as (++j * --k)
        5) Before addition occurs, all the side effects must be resolved;
        6) Partial ordering is present but subexpression evalutation is still indeterminately sequenced;
        7) function executions are always indeterminately sequenced; */

    printf("%d\n", ++i + ++j * --k); // perfectly safe, but beware of what you're doing.

    return EXIT_SUCCESS;
}

