#include "bar.h"


/* During preprocessing, the contents of bar.h are included in this file */
int main(void)
{
    return func(); // declared somewhere
}

/* Defined, but declared in bar.h */
int func(void)
{
    return 0;
}
