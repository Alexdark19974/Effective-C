#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Order of Evaluation
    Page: 64
*/


int glob; // static storage initialized to 0, file-scope object

int f(void) {
    return glob + 10;
}

int g(void) {
    glob = 42;
    return glob;
}

int max(int val1, int val2) {
    return val1 > val2 ? val1 : val2;
}

void order_of_evaluation_for_function_arguments_sequenced() {

    /* the 1st expression is evaluated before the second expression 
     * exoression statement (";") guarantees sequencing */
    int f_val = f(); // sequenced
    int g_val = g(); // sequenced after the previous expression
    int max_value = max(f_val, g_val);

    printf("max_value = %d\n", max_value);
}

void order_of_evaluation_for_function_arguments(void) {

    // 2 ways are possible:
    // 1) f() is invoked first;
    // 2) g() is invoked first;
    // 3) the return value of max() will be different (52 or 42)

    int max_value = max(f(), g()); // the order of evaluation of arguments to max() is unspecified
    // sequencing guarantees:
    // 1) f() and g() are invoked first before max();
    // 2) executions of f() and g() do not interleave, though they share common object glob

    printf("max_value = %d\n", max_value);
}

int main(void) {

    // the order of evaluation of the operands of any C operator and of any subexpressions is generally unspecified;
    // constraints of the order of evaluation:
    // 1) operator precedence and associativity;

    // the compiler will evaluate the same expression differentlly
    // Allowing for more optimized code;
    
    order_of_evaluation_for_function_arguments();
    glob = 0; // file-scope object
    order_of_evaluation_for_function_arguments_sequenced();
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
