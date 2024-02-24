#include <stdio.h>

/* Chapter 2: Object, Functions, and Types
    Subchapter: Swapping Values (Second Attempt)
   Pages: 16 - 18 */

/* swap by pointers: copies of &a. &b are passed as arguments which, upon
   dereferencing, poin to the original objects from main()
   This is pass-by-reference */
void swap(int *, int *); // declared as function acceptinmg 2 params of type pointers to int

int main(void)
{
    int a = 21;             // a: 21
    int b = 17;             // b: 17

    /* swap by pointers: copies of &a. &b are passed as arguments which, upon
       Dereferencing, poin to the original objects from main()
       &a, &b and pa, pb have different addresses, but point to the the same location
       This is call-by-reference or pass-by-reference */
    swap(&a, &b); // unary & address-of operator generates addresses of local variables a and b
    printf("main: a = %d, b =-%d\n", a, b);     // a: 17    b: 21
    return 0;
}

void swap(int *pa, int *pb) { // pa -> a : 21 pb -> b: 17
    /* Unary operator '*' dereferences the pointer to an object */
    int t = *pa;                // t : 21
    *pa = *pb;                  // pa -> a : 17     pb -> b: 17
    *pb = t;                    // pa -> a : 17     pb -> b : 21
    return;
}

