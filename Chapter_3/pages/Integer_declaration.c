#include <stdio.h>
#include <stdlib.h>

/* Chapter 3: Arithmetic Types */
/* Subchapter: Declaring Integers */
/* Pages: 36 */

void declare_integers(void);

int main(void)
{
    declare_integers();

    return EXIT_SUCCESS;
}

void declare_integers(void)
{
    {
        /* all integers, except for char, default to being a signed type, unless explicitly stated otherwise */
        unsigned int ui; // unsigned is required

        /* when declaring integers, "int" keyword can be omitted unless it's the only keyword */
        unsigned u; // int can be omitted

        /* explicitly state "unsigned" unless you want an object to be signed */
        unsigned long long ull2; // int can be omitted

        /* signess of char type is implementation defined (can be either unsigned or signed by default) */
        unsigned char uc; // unsigned is required
    }

    {
        int i; // signed can be omitted
        signed long long int sll;
        long long int sll2; // signed can be omitted
        long long sll3; // signed and int can be omitted

        /* Again, whether char is signed or unsigned by default is implementation-defined */
        signed char sc; // signed is required
    }
}

