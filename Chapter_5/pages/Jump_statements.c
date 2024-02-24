#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

/* Chapter 5: Flow Control
    Subchapter: Jump Statements
        1) The goto-Statement;
        2) The continue-Statement;
        3) The reak-statement;
        4) The return statement;
   Pages: 93 - 97 */

typedef struct object_t {
    char str[256];
} object_t;

int do_something(void)
{
    FILE *file1, *file2;
    object_t *obj = NULL;

    int ret_val = 0; // Initially assume a successful return value

    /* The resources allocated will be released following the "LIFO" order */
    /* alloc 1, 2, 3 -> dealloc 3, 2, 1 */
    /* in this example, goto-s simplify error processing */
    /* using if-else statements would result in duplication of code */
    file1 = fopen("a_file", "w");
    if (file1 == NULL) {
        ret_val = -1;
        goto FAIL_FILE1; // jump to section following the FAIL_FILE1 label
    }                    // no need to deallocate anything

    file2 = fopen("another_file", "w");
    if (file2 == NULL) {
        ret_val = -1;
        goto FAIL_FILE2; // jump to section following the FAIL_FILE2 label
                         // deallocate file1
    }

    obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        ret_val = -1;
        goto FAIL_OBJ;  // jump to section following the FAIL_OBJ label
    }                   // deallocate file2, file1

    // Operate on allocated resources

    // Clean up everything
    free(obj);

FAIL_OBJ:   // Otherwise, close only the resources we opened;
    fclose(file2);
FAIL_FILE2:
    fclose(file1);
FAIL_FILE1:
    return ret_val;
}

void goto_statement(void)
{
    /* Excessive use of goto-statements may lead to spaghetti code 
       Meaning that jumping up and down the sections of code
       Make code harder to read and follow */

    /* Some of the "clean" ways to use goto-statement:
       1) exiting the nested loops;
       2) using them to process errors, esp. if expressions are nested;
       3) avoid excessive use of if-else statements */

    if (0 == do_something()) {
        fprintf(stdout, "Did something.\n");
    } else {
        fprintf(stderr, "Failed to do something.\n");
    }
}

void continue_statement(void)
{
    /* continue statement provides a jump to the end of the loop body
       Regardless of code following the continue statement */

    for (int i = 0; i < 10; ++i) {
        if (i == 5) {
            // goto END_LOOP_BODY; // this is equivalent behavior for continue
            continue; // jump to the end of the loop body
            i = 0; // this line will not be executed
        }
// END_LOOP_BODY: ; // this is our continue statement
    }

}
size_t find_element(size_t len, char arr[len], int key) {
    size_t pos = (size_t)-1;
    printf("pos = %lu\n", pos);
    // traverse arr and search for key
    for (size_t i = 0; i < len; ++i) {
        if (arr[i] == key) {
            pos = i;
            break;  // terminate loop
            // code here will not be executed
        }
    }
    return pos;
}

void break_statement(void)
{
    /* break statement terminates execution of a switch stement or iteration statement */
    /* the program execution resumes at the statement following the switch or loop */
    char c;
    for (;;) {
        puts("Press any key, Q to quit: ");
        c = toupper(getchar());
        if (c == 'Q') /* goto END_OF_LOOP;*/ break;
    }
// END_OF_LOOP:
// Loop exits only when the uppercase or lowercase 'Q' is pressed

    char arr[] = "abcdefghklmnop";
    size_t element = find_element(sizeof(arr), arr, 'y');
    if (element == ULONG_MAX) {
        fprintf(stderr, "failed to find element in arr (%s)\n", arr);
    } else {
        fprintf(stdout, "element = %lu\n", element);
    }
}

int absolute_value(int a)
{
    if (a < 0) {
        return -a;
    }
    // undefined behavior if a non-void function does not have a return statement with an expression / value
    return a;
}

int sum(int x, int y, int z)
{
    return x + y + z; // return statement will return value of x + y + z expression of return type (int)
}

void return_statement(void)
{
    /* return statement terminates execution of the current function 
       and returns control to its caller */
    /* function may have 0 or more return statement */

    printf("%d\n", sum(10, 15, 20));
}

int main(void)
{
    /* Jump statements perform an unconditional jump / transfer
       To another section of the same function
       When encountered */

    goto_statement();

    continue_statement();

    break_statement();

    return_statement();

    return EXIT_SUCCESS; // return 0 to be evaluated as successful termination
}

