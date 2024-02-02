#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 2: Object, Functions, and Types
        Subchapter: Scope
    Pages: 18 - 19
*/

int j;  // file scope of j begins

void f(int i)                       // block scope of i begins 
{
    int j = 1;                      // block scope of j begins; hides file-scope j
    i++;
    for (int i = 0; i < 2; i++) {   // block scope of loop-local i begins
        int j = 2;                  // block scope of the inner j begins; hides outer j and file-scope j
        printf("j = %d\n", j);          // inner j is in scope, prints 2 but not 0 or 1
    }
    printf("j = %d\n", j);              // the outer j is in scope, prints 1
}   // the block scope of i and j ends

void g(int j);                      // j has function prototype scope; hides file-scope j

int main(void)
{
    /* Scope delimits the contiguous region where object can be accessed */
    /* There are 4 types of scope:
     * 1) file scope; // accessed from anywhere including from other files
     * 2) block scope; // accessed within the block or compound statement
     * 3) function prototype; // accessed within the function prototype
     * 4) function scope; // accesses from the opening to the closing brackets */

    int i = 0; // block scope (main() {})
    j = 3;                          //  j has file scope, akin to "extern j;"
    printf("j = %d\n", j);          // file-scope j prints 3
    f(i);
    printf("j = %d\n", j);          // file scope j prints 3

    /* nested scope */
    /* Inner scopes must be contained inside outer scopes */
    { // outer scope; doesn't have acces to inner scope
        int i = 10;
        { // inner scope; has access to outer scope, hence accessing 'i'
          // int i = 11; // this variable is in inner scope, which takes precedence over outer scope
          // 11 will be output
            printf("i from outer scope is %d\n", i);
            int i = 1;
            printf("i from inner scope is %d\n", i);
        }
        printf("i exiting the inner scope is %d\n", i);
    }
    goto exit;

exit: // labels have function scope only
    return EXIT_SUCCESS;
}

