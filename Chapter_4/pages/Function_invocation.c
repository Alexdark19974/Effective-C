#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Function Invocation
    Page: 60
*/

int max(int x, int y) {
    return x > y ? x : y;
}

int f(void) {
    return 0;
}

#if 0
void g (int func(void)) { // also possible
#else
#if 0
void g(int (*)(void)) { // available for C2X
#else
void g(int (*func)(void)) {
#endif
#endif
    if (func() != 0) {
        printf("g failed\n");
        return;
    }
}

int main(void)
{
    int x = 11;
    int y = 21;
    /* max is a function designator 
     * that is converted to a pointer to a function at compile time */
    int max_of_x_and_y = max(x, y);

    // passing function as an argument
    g(f); // function designator "f" is converted to (*)(void)

     return EXIT_SUCCESS;
}
