#include <stdio.h>
#include <stdlib.h>

/* Chapter 2: Object, Functions, and Types
    Subchapter: Type Qualifiers
   Pages: 32- 34 */

void type_qualifiers(void);
void const_qualifier(void);
void cast_const_away(void);
void volatile_qualifier(void);
void restrict_qualifier(void);

int main(void)
{
    /* unqualified types are the type you use by default: int, double, char, etc. */
    /* Qualified types changes the behavior of qualified objects */
    /* Qualifiers: const, volatile, and restrict */

    type_qualifiers();

    return EXIT_SUCCESS;
}

void type_qualifiers(void)
{
    const_qualifier();
    volatile_qualifier();
    restrict_qualifier();
}

void const_qualifier(void)
{
    /* Objecs declared with the const qualifier are not modifiable */
    /* They are read-only, not assignable but can have constant intializers */
    const int i = 1; // const-qualified int initialized to 1
    // i = 2; // error: i is const-qualified

    /* Modiying const object is a bad idea */
    /* Becasuse we change the object's value in ROM segment */
    int *ip =(int *) &i;
    *ip = 2; // undefined behavior
    printf("i = %d (UB)\n", *ip);

    cast_const_away();
}

void cast_const_away(void)
{
    /* const qualifier can be cast away if a pointer points to const object
       But the original object is not const-qualified */
    int i = 12;
    const int j = 12;
    const int *ip = &i;
    const int *jp = &j;
    *(int *) ip = 42; // ok
    /* Otherwise, it's all undefined behavior and memory faults */
    *(int *) jp = 42; // undefined behavior
    printf("i = %d\n", *ip);
    printf("j = %d (UB)\n", *jp);
}

void volatile_qualifier(void)
{
    /* volatile-qualified objects lets the compiler know */
    /* that the value of the object may unexpectedly change */
    /* Therefore, optimizations are not applied to volatile objects */
    int i = 0;
    /* if not for volatile qualifier, this section of code may be removed */
    /* Because it is not consequential */
    volatile int increment;
    increment++; // dissasemble this code to see if the variable and its operatiosns persist

    printf("i = %d\n", i);
}

void restrict_qualifier(void)
{
    /* restrict-qualified objects promote optimization */
    /* restrict tells the compiler that a restrict-qualified object will not
       overlap with another object in terms of memory location */
    typedef void func(unsigned int, int * restrict, int * restrict);
    int src[2] = {1 , 2};
    int dest[2] = {0};
    func f;
    /* Be VERY careful when using restrict cause it might lead to memory faults */
    f(sizeof(dest) / sizeof(*dest), dest, src);

    printf("dest[0] = %d, dest[1] = %d\n", dest[0], dest[1]);
}

void f(unsigned int n, int * restrict p, int * restrict q) {
    while(n--> 0) {
        *p++ = *q++;
    }
}

