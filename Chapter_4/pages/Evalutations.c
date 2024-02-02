#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Evaluations
    Page: 59
*/

int f(void) {
    return 1;
}

int main(void)
{
    /* Evaluation is the process of value computation and the initiation of side
     * Effects that typically result in simplying an expression 
     * Down to a single value
     * */

    /* Value computation is the calculation of the value resulting from
     * An evaluation of the expression:
     * 1) Determining the identity of the object;
     * 2) Reading the value previous assigned to an object; 
     * */

    /* Side effects are changes to the state of the execution environment:
     * 1) Writing to an object;
     * 2) Accessing (R/W) a volatile-qualified object;
     * 3) I/O;
     * 4) Assignment;
     * 5) Function invocation that does any of the aforementioned things;
     */

    int a[1000] = {100};
    int j;
    int i = 0;

    /* value of a, i, and a[i] are computed
     * As well as the computation of addition 
     * All value computations of the operands must occur before
     * Before computing the final value
     * Function is not computed but may contain side effects too
     * */
    j = a[i] + f() + 9;

    /* The side effect of the operation above is the assignment of value to j */

     return EXIT_SUCCESS;
}
