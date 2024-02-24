#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

/* Chapter 6: Dynamically Allocated Memory
        Subchapter: Flexible Array Members (FLAs)
    Pages: 110 - 111
    Useful sources:
        1) https://stackoverflow.com/questions/3711233/is-the-struct-hack-technically-undefined-behavior
        2) https://gcc.gnu.org/onlinedocs/gcc-4.5.0/gcc/Zero-Length.html#Zero-Length
        3) https://stackoverflow.com/questions/9722632/what-happens-if-i-define-a-0-size-array-in-c-c
        4) https://tonywearme.wordpress.com/2011/07/26/c-struct-hack/
        5) https://www.kernel.org/doc/html/v5.16/process/deprecated.html#zero-length-and-one-element-arrays */

void flexible_array_members(void);

typedef struct {
    size_t num;
    int data[]; // variable-size array: size is defined at runtime (available since C99)
} widget;

typedef struct {
    size_t num;
    // int data[0]; // works but prohibited now
    int data[1]; // also works but takes more memory
    //  int data[]; compatible with C99; always use it over data[0] and data[1];
} Widget;

void *func(size_t array_size)
{
    /* Do NOT access array member unless you explicitly allocated memory for it (undefined behavior) */
    widget *p = (widget *)malloc(sizeof(widget) + sizeof(int) * array_size); // beware of integer overflow
    if (p == NULL) {
        return NULL;
    }

    p->num = array_size;
    for (size_t i = 0; i < p->num; ++i) {
        p->data[i] = 17;
    }

    return p;
}

int main(void)
{
    flexible_array_members();

    return EXIT_SUCCESS;
}

void flexible_array_members(void)
{
    /* Flexible array members were introduced in C99 */
    /* When declaring a struct with array of incomplete type ("data[]") */
    /* You need to allocate memory for it yourself */
    /* The flexible array must be the last member of the struct */
    /* And the structure itself must contain > 1 members */

    printf("size of widget is %lu\n", sizeof(widget)); // size is 8 because size_t (4) + extra 4 bytes of padding to acommodate an array member
    printf("size of Widget is %lu\n", sizeof(Widget)); // size is 16 (why? Probably extra padding?)
    widget *p = func(12);
    if (p) {
        for (size_t i = 0; i < p->num; ++i) {
            printf("data[%lu] = %d\n", i, p->data[i]);
        }
    }

    free(p);
    p = NULL;
}

