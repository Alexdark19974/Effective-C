#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/* Chapter 5: Flow Control
    Subchapter: Interation Statements: While, Do-While and For statements
   Pages: 89 - 92 */

void do_while_example(void)
{
    int count; float quant; char units[21], item[21];

    /* Read from stdin at least once, then check for errors or EOF */
    do {
        count = fscanf(stdin, "%f%20s of %20s", &quant, units, item);
        fscanf(stdin, "%*[^\n]");
        printf("%f %.5s of %.5s\n", quant, units, item);
    } while(!feof(stdin) && !ferror(stdin));
}

void f(unsigned int x)
{
    /* Evaluation of controlling expressions */
    /* Occurs before each execution of the loop body */
    while (x > 0) { // execution from x down to 1
        printf("%d\n", x);
        --x;
    }
    printf("after while loop %d\n", x);
    return;
}

/* if n is larger than size of dest, buffer overflows and undefined behavior occurs */
void *_memset(void *dest, int val, size_t n)
{
    unsigned char *ptr = (unsigned char *)dest; // explicitly cast void * to unsigned char *
    printf("n = %lu\n", n); // 15
#if 1
    /* This is by far the BEST implementation of memset() with while loop */
    while (n-- > 0) {// n decerements as a side effect of evaluation
                     // n is already decremented here
        printf("n = %lu\n", n); // 14
        *ptr++ = (unsigned char)val; // from ptr up to ptr + n - 1
    }
#else
#if 0
    /* Also possible but more obscure and error prone; genetrates a warning  */
    /* Unsigned n will never be less than 0, thus the condition is always true */
    /* the left operand of && operator makes sure n is at least more than 0 */
    while (n && --n >= 0) {// n decerements as a side effect of evaluation
                     // n is already decremented here
        printf("n = %lu\n", n); // 14
        *ptr++ = (unsigned char)val;
    }
#else
#if 0
    /* Less prone to errors but beware of wraparound if n == LONG_MAX */
    ++n;
    while (--n > 0) {// n decerements as a side effect of evaluation
                     // n is already decremented here
        printf("n = %lu\n", n); // 14
        *ptr++ = (unsigned char)val;
    }
#else
    /* Using pointer arithmetic and the fact that we can peek into 1 byte outside of dest boundary */
    /* Uses more memory */
    unsigned char *ptr_end = ptr + n;
    while (ptr - ptr_end < n) {// n decerements as a side effect of evaluation
                     // n is already decremented here
        printf("n = %lu\n", n); // 14
        *ptr++ = (unsigned char)val;
    }
#endif
#endif
#endif

    /* n == 0, then while exits, and n is decremented as a side effect */
    printf("n = %lu\n", n); // will print ULONG_MAX due to wraparound
    return dest;
}

void *__memset(void *dest, int val, size_t n)
{
    unsigned char *ptr = (unsigned char *)dest;

    /* 1) clause 1 declares and initializes a loop counter once, when for-loop is entered;
       2) expression 2 is the controlling expresssion that is evaluated before executing the loop body;
       3) expression 3 performs some useful actions, usually incrementing the loop counter */

    for (/* clause 1*/size_t i = 0; /*expression 2*/ i < n; /*expression 3*/ ++i) {
        /* body */
        *(ptr + i) = val;

        /* Upon reaching the end of the body, the execution is passed to expression 3 which is evaluated, then expression 2 is evaluated */
    }

    /* for-loop is analagous to while-loop: */
    /* size_t i = 0; // clause 1
       while(i < n) { // expression 2
            *(ptr + i) = val;
            i++; // expression 3
       } */
    return dest;
}

struct node {
    int data;
    struct node *next;
};
struct node *p;
struct node *head;

void show_misleading_for_loop(void)
{
    if (!head) {
        head = (struct node *) malloc(sizeof(struct node));
        if (!head) {
            fprintf(stderr, "Failed to allocate memory for head.\n");
            perror("malloc");
            abort();
        }
    }

    head->data = 1;
    head->next = NULL;

    p = (struct node *) malloc(sizeof(struct node));
    if (!p) {
        fprintf(stderr, "Failed to allocate memory for p.\n");
        perror("malloc");
        abort();
    }

    /* This is erroneous because we're accessing freed memory */
    /* 1) head is assigned to p */
    /* 2) controlling expression is evaluated \
       3) p is freed
       4) expression tries to assign field of p to p by accessing to p that has been freed
       5) CRASH */
#if 0
    for (/* clause 1*/p = head; /*expression 2*/p != NULL; /*expression 3*/ p = p->next) {
        /* body */
        free(p);
        p = NULL;
        /* This will not work */
    }
#endif
    struct node *q;

    for (p = head; p != NULL; p = q) {
        /* Store the next node in q , then free the p block */
        q = p->next;
        free(p);

        /* assign q to p (next block) */
    }

}

void while_statement(void)
{
    f(10);
    char str[15];
    _memset(str, 0, 15);
    strcpy(str, "Hello, World!\n");
    printf("str = %s\n", str);
}

void do_while_statement(void)
{
    unsigned int n = 10;

    /* At least 1 subexpressions is executed */
    do {
        printf("n = %d\n", n);
    } while(--n > 0);

    printf("after do-while loop %d\n", n);

    do_while_example();
}

void for_statement(void)
{
    char str[128];

    __memset(str, 0, sizeof(str));

    show_misleading_for_loop();
}

int main(void)
{
    while_statement();
    do_while_statement();
    for_statement();

    return EXIT_SUCCESS;
}

