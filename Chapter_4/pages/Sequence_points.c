#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Sequence Points
    Page: 66
*/

void show_unsequenced_expressions(void)
{
    /* Unsequenced expressions: 
       1) May interleave;
       2) Double Write (+ Read) of the same object in the same expression;
       3) Undefined Behavior;
       */
    int i = 5;
    printf("Result = %d\n", i++ * i++); // unsequenced -> UB

    /*
     * If a side effect is unsequenced relative to either a different side effect
     * On the same scalar or a value computation
     * That uses the value of the same scalar object,
     * The behavior is undefined.
     * */
}

int main(void)
{
    /* A sequence point is a juncture at which all side effects are resolved;
     * Sequence points exist between full expressions;
     * Guaranteed sequence points:
     * 1) full expresions (designated by ";" operator);
     * 2) entering/exiting a function;
     * 3) comma operator;
     * */

    int i = 5; // sequenced
    /* all side effects are resolved */
    int j = i++; // sequenced
    /* all side effects are resolved */
    int k = i++; // sequenced
    /* all side effects are resolved */

    show_unsequenced_expressions();

    return EXIT_SUCCESS;
}
