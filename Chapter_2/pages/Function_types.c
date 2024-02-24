#include <stdio.h>
#include <stdlib.h>

/* Chapter 2: Objects, Function and Types
    Subchapter: Function Types
   Pages: 24 - 25 */

/* if the declarator includes a parameter type list
   And a definition, the declaration of each parameter
   Must include an identifier except void parameter */
void function_types(void)
{
    /* Function types are derived types */
    /* Their type is derived from:
        1) the return type;
        2) the number and types of its parameters; */

    /* the name of a function is a function declarator as well as its return type */
    /* the function declarations down below are function prototypes */
    int f(void); // use void in parameter list if function accepts no parameters
    int *fip(); // accepts any number and types of arguments // unsafe to use, unportable to C++ (empty parameter list means void in C++)
    void g(int i, int j); // identifiers are optional
    void h(int, int); // declaration of function without definition: identifiers are not necessary
    int max(int a, int b);

    printf("max = %d\n", max(1, 2));
}

int main(void)
{
    function_types();

    return EXIT_SUCCESS;
}

/* Definition of function 'f' is its implementation */
int f(void)
{ // the function body
    return 0;
}

int max(int a, int b)
{ return a > b ? a : b; }
