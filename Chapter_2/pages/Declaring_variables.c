#include <stdio.h>

/* Chapter 2: Object, Functions, and Types
    Subchapter: Declaring variables
   Pages: 14 -15 */

void swap(int, int); // defined later, now only declared
void show_declaring_multiple_variables(void);

int main(void)
{ // comound statement or block
  // Each variable must have a declaration
    int a = 21; // declared variable with identifier 'a' of type int with an initializer of 21; defined
    int b = 17; // declared variable with identifier 'b' of type int with an initializer of 17; defined
    int c; // declared variable with identifier 'b' of type int; not defined

    // swap(a,b); // this will fail due to lack of definition of swap function
    // printf("main: a = %d, b = %d\n", a, b);

    show_declaring_multiple_variables();
    return 0;
}

void show_declaring_multiple_variables(void)
{
    /* you can declare multiple variables in a single declaration */
    char *src, c; // declare a variable "src" of pointer to char  and variable 'c'of type char
    int x, y[5];
    int m[12], n[15][3], o[21];
    /* but doing so can be confusing due to different object types */

    /* This code is easier to understand
       char *src;
       char c;
       int x;
       int y[5];
       int m[12];
       int n[15][3];
       int o[21];
       But it takes more space */
}

