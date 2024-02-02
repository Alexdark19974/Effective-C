#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void variadic_macros(void);
void type_generic_macros(void);

int main(void)
{
    type_generic_macros();
    variadic_macros();

    return EXIT_SUCCESS;
}

/* WARNING: relevant to >= C11 standard! */
void type_generic_macros(void)
{
    /* Type-generic macros allow you to invoke particular behavior depending on the type of the argument
     * For example, invoking functions such as sin, sinf, sinl depending on the underlying type of the argument
     * That is passed to the type-generic macro.
     *
     * A generic selection expression maps
     * The type of its unevaluated operand expression To an associated expression
     * Consider it switch-case but in terms of types, not the values of objects
     * */

#define sin(X) _Generic((X), \
    float: sinf, \
    double: sin, \
    long double: sinl,\
    default: sinf \
    )(X)

    double ld = sin(1.2500000);
    printf("ld = %f\n", ld);
}

/* Relevant for >= C89 standard*/
void variadic_macros(void)
{
    /* Variadic macros are like variadic functions, meaning you can pass an arbitrary amount of arguments
     * To a function such printf, etc. */
#define VARIADIC_PRINT(stream, fmt, args...) fprintf(stream, fmt, ##args) // Token pasting
    VARIADIC_PRINT(stdout, "%s %s %s %s", "Hello", "World!", "\n", "Hi");
}
