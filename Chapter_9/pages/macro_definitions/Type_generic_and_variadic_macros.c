#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void variadic_macros(void);
void type_generic_macros(void);

/* Additional sources:
   1) https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
   2) https://gcc.gnu.org/onlinedocs/gcc-4.2.1/gcc/C-Extensions.html#C-Extensions
   3) https://gcc.gnu.org/onlinedocs/gcc-4.2.1/gcc/Variadic-Macros.html */

int main(void)
{
    type_generic_macros();
    variadic_macros();

    return EXIT_SUCCESS;
}

/* NOTE: type_generaic_macros are relevant to >= C11 standard! */
void type_generic_macros(void)
{
    /* Type-generic macros allow you to invoke particular behavior depending on the type of the argument
       For example, invoking functions such as sin, sinf, sinl depending on the underlying type of the argument
       That is passed to the type-generic macro.
       A generic selection expression maps
       The type of its unevaluated operand expression To an associated expression
       Consider it switch-case but in terms of types, not the values of objects */

/* Uncomment this and compile with -lm -std=c11 or above */
/* #define sin(X) _Generic((X), \
    float: sinf, \
    double: sin, \
    long double: sinl,\
    default: sinf \
    )(X)

    double ld = sin(1.2500000);
    printf("ld = %f\n", ld);\
*/
}

void variadic_macros(void)
{
    /* Variadic macros are like variadic functions: you can pass an arbitrary amount of arguments
     To a function such printf, etc. */

    /* NOTE: using the following syntax with flags -std=c99 -pedantic will generate
       -pedantic - excludes GNU/GCC extentions for C language
       A warning about variadic macros. Use -Wno-variadic-macros to supress it
       Strictly speaking, the syntax below does not conform to C standard (c89, c90, c99) */

/* This is a GCC extension*/
#define VARIADIC_PRINT0(fmt, args...) fprintf(stderr, fmt, args) /* No token pasting operator */
    VARIADIC_PRINT0("%s\n", "This is GCC extention of a Variadic Macro without token pasting");

#define VARIADIC_PRINT1(fmt, args...) fprintf(stderr, fmt, ##args) /* With token pasting operator */
    VARIADIC_PRINT1("%s\n", "This is GCC extention of a Variadic Macro");

    /* This syntax strictly conforms to C99 standard */
#define VARIADIC_PRINT2(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
    VARIADIC_PRINT2("%s\n", "This is a c99 Standrad Variadic Macro");

    /* This conforms to c99 too */
#define VARIADIC_PRINT3(...) fprintf(stderr, __VA_ARGS__)
    VARIADIC_PRINT3("This is a c99 Standrad Variadic Macro too\n");

/* This syntax is an extention too and allows us to bypass the requirement of at least 1 argument in C99 standard */
#define VARIADIC_PRINT4(fmt, ...) fprintf(stderr, fmt,  ## __VA_ARGS__)
    VARIADIC_PRINT4("This is a GCC Standrad Variadic Macro too\n");
}

