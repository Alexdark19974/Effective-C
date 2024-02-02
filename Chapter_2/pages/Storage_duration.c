#include <stdio.h>
#include <stdlib.h>

/* 
    Chapter 2: Objects, Functions and Types
        Subchapter: Storage Duration
    Pages: 19 - 20
*/

int f; // file-scope variable of static storage duration, initialized prior to program start-up

void increment(void)
{
    static unsigned int counter = 0;                // static object's lifetime is the entire execution of the program
    counter++;
    printf("counter = %d\n", counter);
} // counter will still exist after exiting the function

int *func(int i) {
    static int l = 1;
    const int j = i; // ok
    static int k = 0/*j*/; // error
    /* const int is a block-scope object with the lifetime of function execution 
     * Whereas static int is a block-scope object with the lifetime of the entire program execution
     * Initialized at the program startup
     * Static objects cannot be initialized with a variable of automatic storage duration
     * Static objects must be initialized with a constant value (1, 'a' or 0xFF, or enum) 
     * Constant values: 1, 'a',0xFF; results of sizeof() and alignof() operators */
    return &k;
}

int main(void)
{
    /* Lifetime of an object is defined by the time
     * During program execution for which:
     * 1) object exists;
     * 2) has specific storage duration;
     * 3) has a constant address; 
     * 4) retains last-stored value; */

    /* There are 4 types of storage duration: 
     * 1) automatic;
     * 2) static;
     * 3) thread;
     * 4) allocated / dynamic; */

    /* Local variables have automatic storage duration
     * Their lifetime is the block where they are declared
     * And until execution leaves it */

    /* Scope applies to identifiers and their access */
    /* Lifetime applies to the time during which an object exists */

    /* Static or global / file-scope  variables have static storage duraion 
     * They are intialized prior to program start-up */

    for (int i = 0; i < 5; i++) { // i has a loop-local scope and automatic storage duration
        increment();
    }
    return 0;
}
