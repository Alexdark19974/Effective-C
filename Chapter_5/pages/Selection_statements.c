#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/*
    Chapter 5: Control Flow
        Subchapter: Selection Statements
            1) if-Statement;
            2) switch-Statement; 
    Pages: 83 - 88
*/

bool safediv(int dividend, int divisor, int *quotient) {
    if (!quotient) return false; // if quotionet is NULL, then the controlling expresion is true, then we execute "return false"
    if ((divisor == 0) || ((dividend == INT_MIN) && (divisor == -1))) // if either of 2 operands of logical OR is true, execute "return false"
        return false;
    *quotient = dividend / divisor;
    return true;
}

void print_grade_if(unsigned int marks) {
    if (marks >= 90) {
        puts("YOUR GRADE : A");
    }
    if (marks >= 80) {
        puts("YOUR GRADE : B");
    }
    if (marks >= 70) {
        puts("YOUR GRADE : C");
    } else {
        puts("YOUR GRADE : Failed");
    }
}

void print_grade_switch(unsigned marks) // compile with -Wswitch-enum
{
    /* controlling expression must have an integer type */
    /* Switch jumps to one of case labels that matches the result of the controlling expression */
    /* It is good practice to add break statement to every case label 
     * Unless you expect a fall-through */
    switch(marks/10) {
        case 10: // fall-through: no warning to due nothing being modified twice;
        case 9:
            puts("YOUR GRADE: A");
            break;
        case 8:
            puts("YOUR GRADE : B");
            break;
        case 7:
            puts("YOUR GRADE : C");
            break;
        default: // default label if none of cases match; supresses compiler warnings
            puts("YOUR GRADE : Failed");
    }
}

typedef enum { Savings, Checking, MoneyMarket /*, CD */ } AccountType; // when adding another enumerator, update case label too
void assignInterestRate(AccountType account)
{
    double interest_rate; // unitialized variable 
    switch(account) { // Will generate a warning if CD is not accounted for
        case Savings: // a fall-through: warning due to interest_rate changing twice
            interest_rate = 3.0;
        case Checking:
            interest_rate = 1.0;
            break;
        case MoneyMarket:
            interest_rate = 4.5;
            break;
        /* new case label for CD */
        /* case CD:
         * interest rate = 7.5
         * break; */
        /* No default case label will not help identify unknown cases */
        /* default: abort(); // abnormal termination of program
         * */
    }
    printf("Interest rate = %g.\n", interest_rate); // possible unitiliazed read (consider it UB)

}

void show_misleading_indentation_of_if_statement(void) {
    int a = 10;
    int b = 20;

    /* Only 1 substatement following the if statement is executed */
    if (a == 10)
        puts("a == 10");
        puts("and b == 20"); // always executed; produces a compiler warning

    /* compound statement delimits a single block that will be executed sequentially */
    if (a == 10) {
        puts("a == 10");
        puts("and b == 20"); // fixed it
    }

    /* it is good practice to always encapsulate substatements with braces to avoid
     * Possible errors and warnings
     * It improves readability of code 
     * */
}

void if_statement(void)
{
    int a = 1;
    int b = 0;
    int c = 8;
    int quotient = 0;
    /* the first if-statement conditionally determines
     * Whether a substatement is executed
     * Ultimately, if-statement boils down to whether a controlling expression
     * Is equal to zero or not
     * */
    if (a) // controlling expression: substatement is execute4d if a != 0
        puts("var a is not equal to 0");

    /* the second kind of if-statement has an else clause 
     * If the controlling expression is false
     * The substatement after "else" is executed */
    if (b) // fisrt condition
        puts("var b is not equal to 0");
    else // alternative condition
        puts("var b is equal to 0");

    if (false == safediv(10, 2, &quotient)) // before executing comparison with relational operator, left and right operands must be evaluated
        abort();

    /* "if ... else ladder" */
    if (a == 2) // if a is true, execute
        puts("a == 2");
    else if (b == 1) // if a is 0 and b is true, execute
        puts("b == 1");
    else if (c == 3) // if a and b are 0 and c is true, execute
        puts("c == 3");
    else // otherwise, execute else clause
        puts("else substatement");

    print_grade_if(90);
    print_grade_switch(90);

    show_misleading_indentation_of_if_statement();

}

void switch_statement(void)
{
    print_grade_switch(109);
    AccountType AT = MoneyMarket;

    assignInterestRate(AT);
}

int main(void)
{
    /* Compile with "-Wswitch-enum" and "-Wfall-through" */
    if_statement();

    switch_statement();

    return EXIT_SUCCESS;
}
