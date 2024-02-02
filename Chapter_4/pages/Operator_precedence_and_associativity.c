#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Operator Precendence and Assoiciativity
    Page: 62
*/

void show_misleading_precedence(void)
{
    char abc[] = "abc";
    char xyz[] = "xyz";
    char *p = abc;

    puts("---------------- misleading precedence ----------------");

    printf("res of ++*p is %c\n", ++*p); // same as ++(*p): dereferenced first, then immediately incremented;

    p = xyz;

    printf("res of *p++ is %c\n", *p++); // same as *(p++): postfix increment returns value, then it is dereferenced
    // after printing the value, p is incremented

    printf("*p after post increment is %c\n", *p);

    printf("abc is %s\n xyz is %s\n", abc, xyz);

    /* When making such complex expressions as *p++ or *++p or ++*p 
     * Always keep in mind precedence and associativity */

    puts("---------------- misleading precedence ----------------");
}

int main(void)
{
    /* Operator precedence is a collection of rules that dictate 
     * The order in which operations are performed in a given expression */
    /* Associativity determines how operators of the same precedence are grouped
     * When no explicit parentheses are uses:
     * 1) Implicit introduction of parentheses;
     * 2) Some operators are left-associated or right-associated 
     * 3) If 2 operatores have the same precedence and association, 
     *    They are evaluate from left to right. */

    int a = 0;
    int b = 1;
    int c = 2;

    // assignment operator is right-associated
    a = b = c; // identical to (a = (b = c));
    printf("a is %d\n", a);

    // additive operator is left-associated
    printf("sum = %d\n", a + b + c); // identical to ((a + b) + c)
    
    int i = 0;

    // multiplication operator has higher precedence than addition operator
    // So b and c are bound together
    // Then addition is performed;
    // Then assignment is performed;
    i = a + b * c; // identical to a + (b * c);

    show_misleading_precedence();

     return EXIT_SUCCESS;
}
