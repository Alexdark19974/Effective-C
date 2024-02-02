#include "bar.h"

/* During preprocessing, the contents of bar.h are included in this file as well as baz.h's */

int main(void)
{
    other_func();

    return func(); // declared somewhere
}

/* Defined, but declared in bar.h */
int func(void)
{
    return 0;
}

/* Declared in baz.h */
int other_func(void)
{

    return 1;
}
