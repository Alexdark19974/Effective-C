#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/* Chapter 2: Object, Functions, and Types
    Subchapter: Boolean Types, and Character Types, Numerical Types
   Pages: 21 - 24 */

void boolean_types(void);
void character_types(void);
void numerical_types(void);
void integer_types(void);
void enum_types(void);
void floating_point_types(void);
void void_types(void);

int main(void)
{
    boolean_types();
    character_types();
    numerical_types();

    return EXIT_SUCCESS;
}

void boolean_types(void)
{
    /* You can use either _Bool or bool (if stdbool.h is included)
        To declare boolean objects that store either 1 or zero */
    _Bool flag1 = 1;
    bool flag2 = false; // stdbool.h allows to assign "false" and "true" which are integer constants 0 and 1, respectively
    /* or you can use macro definitions to define boolean values */
#define TRUE 1
#define FALSE 0
    flag1 = TRUE;
    flag2 = FALSE;

    /* And you can use typedef to make a derived boolean type */
typedef unsigned int boolean;
    boolean bool1 = true;
    boolean bool2 = FALSE;
    printf("bool1 = %u, bool2 = %u\n", bool1, bool2);
}

void character_types(void)
{
    /* C defines 3 character types:
        1) char;
        2) signed char;
        3) unsigned char; */

    /* Each complier will either define "char" either
       As "signed char" or "unsigned char"
       Either way, "char" stands out as a separate char type */

    /* char type is used to represent basic execution character set:
        1) letters (upper-/lower case);
        2) 10 decimal digits;
        3) punctuation characters;
        4) space characters;
        5) control characters; */

    /* Don't use "char" to represent integers
       Use signed char to represent small signed integers
       Use unsigned char to represent small non-zero integers */

    char some_character = -1; // my implementation defines char as signed char
    char arr[] = "abcdefghklmnopqrstxqwxyz0123456789!?.,;";

    printf("arr = %s, sizeof arr is %lu\n", arr, sizeof(arr));

}

void numerical_types(void)
{
    /* Numerical types represent:
        1) integers;
        2) floats;
        3) enumerators; */

    integer_types();
    enum_types();
    floating_point_types();
    void_types();
}

void integer_types(void)
{
    /* There are 2 kinds of integers:
        1) Signed;
        2) Unsigned; */

    /* Signed integers represent negative, positive numbers, and zero*/
    /* Signed integers : signed char, short int, int, long int, long long int */
    /* "int" keyword (except for int itself) can be omitted: short, long, long long */
    /* Unsigned integers represent positive numbers and zero*/
    /* Unsigned integers : unsigned char, unsigned short int, unsigned int, unsigned long int, unsigned long long int */
    /* "int" keyword can be omitted: short, long, long long */

    /* Width is the size of an object in bits: 8, 16, 32, 64 bit width  */
    /* Wider types can include narrower types (long long can include long, etc.) */

    unsigned val = 0; // will default to unsigned int
    long long long_val = LONG_MAX;
    unsigned long long ulong_val = UINT_MAX;

    printf("val = %u\nlong_val = %lld\nulong_val = %llu\n", val, long_val, ulong_val);
}

void enum_types(void)
{
    /* enum/enumeration allows you to define a type that assigns names
       To integer values in cases with an enumerable set of constant values
       Such names are called enumerators */

    /* If you don't assign a number to the 1st enumerator, the count
       Starts from 0
       Each subsequent enumerator is incremented by 1 */

    enum day { sun, mon, tue, wed, thu, fri, sat };

    /* You can assign specific values to enumerators */
    enum cardinal_points {north = 0, east = 90, south = 180, west = 270 };

    /* Starts with 1, then gets incremented by 1 */
    enum months { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

    /* The underlying type of an enumerator is int (unsigned int for GCC) */
}

void floating_point_types(void)
{
    /* C language supports 3 floating-point types:
        1) float;
        2) double;
        3) long double;
      The floating point implementation is implementation dependent.
      Chapter 3 explains floats in great detail. */
}

void void_types(void)
{
    /* void is a derived type, meaning it can hold no value */
    /* As a return value of function, nothing is returned */
    /* As a parameter, the function accepts no arguments */
    /* As a void * (pointer to void), it can reference any object */

    void *ptr = NULL;
    ptr = &main; // you should not assign pointer to function to just a pointer -> will produce a warning
    /* do NOT dereference void pointer */
    printf("address of main function is %p\n", ptr);
    int (*ptr_to_func)(void);
    ptr_to_func = &main;
    printf("address of main function is %p\n", (void *) ptr_to_func); // will produce a different warning
}

