#include <stdio.h>
#include <stdlib.h>

typedef int *(*fp)(void); // fp is an alias for int * (*)(void)
typedef int *fpp(void);

int *increment(void)
{
    static int counter = 0;
    counter++;
    return &counter;
}

int main (void) {
    int *ret = 0;
    int *(*non_typedef_ptr)(void);
    fpp *func;
    int *fv(void);

    // fv = increment;
    fp func_ptr;
    // func_ptr = increment;
    func_ptr = &increment; // is the same as line 20
    ret = func_ptr();
    printf("ret = %d\n", *ret);

    non_typedef_ptr = func_ptr;
 
    non_typedef_ptr(); 
    printf("ret = %d\n", *ret);

    ret = (**********************non_typedef_ptr)(); // non_typedef_ptr will just keep dereferencing to itself, nothing criminal here;
    printf("ret = %d\n", *ret);

    func = fv;
    func_ptr = &fv; // is the &fv analagous to int *ip = &i; even though it is a function ?

    func_ptr();
    func();

    return EXIT_SUCCESS;
}

int *fv(void) {
    printf("return 0\n");
    return NULL;
}

