#include "bar.h"
#include "bar.h" // the contents of the header will be ignored

int main(void)
{

    return func(); // declared somewhere
}

/* Defined, but declared in bar.h */
int func(void)
{
    return 0;
}

