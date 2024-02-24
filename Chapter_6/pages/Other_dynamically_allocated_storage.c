#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Chapter 6: Dynamically Allocated Memory
    Subchapter: Other Dynamically Allocated Storage
        1) The alloca Function;
        2) Variable-Length Arrays;
   Pages: 111 - 115 */

void other_aspects(void);
void alloca_function(void);
void variable_length_arrays(void);
void block_scope_vlas(void);
void function_prototype_scope_vlas(void);
void func(size_t);
void printerr(int, size_t);
void sizeof_side_effect(void);
void printerr(/*errno_t*/int errnum); // errno_t is C11 typedef

int main(void)
{
    other_aspects();
}

void other_aspects(void)
{
    /* Any C-programs are located in memory, in the shape of stack frame.
       Stack is data structure that enables C-programs to implement nested invocation
       Of functions at runtime
       Each function invocation creates another stack frame, and so forth.
       Stack follow LIFO (last-in-first-out) pattern. */
    alloca_function();
}

void alloca_function(void)
{
    /* alloca() allows dynamic allocation from the stack rather than the heap at run time */
    /* It is an intrinsic function meaning that it's up to a compiler how to implement alloca() */
    /* On x86 architecture, the compiler substitues alloca() with a single instruction to adjust
       The stack pointer tp accommodate the additional storage */
    printerr(ENOMEM);
}

void printerr(int errnum)
{
    /* rsize_t */size_t size = 128/*strerrorlen_s(errnum) + 1*/; // rsize_t is C11 typedef as well as strerrorlen_s()
    /* Alloca doesn't return NULL if an error occurs */
    /* You may also exceed the bounds of the stack: compile with -Walloca and -Walloca-larger-than=size  */
    char *msg= (char *) alloca(size); // allocate 128 (or more depending on mem location) from stack
    if (errnum == ENOMEM) {
        snprintf(msg, size, "%s", "No memory left");
    } else {
        snprintf(msg, size, "%s", "Unknown error");
    }
    /* if (strerror_s(msg, size, errnum) != 0) { // C11 typedef
        fputs(msg, stderr);
    }
    else {
        fputs("unknown error", stderr);
    } */
    fprintf(stdout, "%s\n", msg);

    /* alloca() does not require you to free() memory because it's automatically freed upon exiting stack frame */
}

void variable_length_arrays(void)
{
    /* Introduced in C99, arrays can be declared using variables at runtime */
    /* VLAs can be either block scope or function prototype scope */

    block_scope_vlas();
    function_prototype_scope_vlas();
}

void block_scope_vlas(void)
{
    func(12);
}

void func(size_t size) // block scope vla
{
    /* The array is allocated in the stack frame */
    /* And freed when the frame exits - just like alloca() */
    int vla[size];

    /* When sizeof() is applied to a VLA
       Its size is calculated at runtime
       (instead of compile time if its size is a constant) */
    printf("Size of VLA is %lu\n", sizeof(vla));
    sizeof_side_effect();

    /* VLAS share similar problems with alloca():
       1) No built-in overflow check when passing the size (esp. when nmemb * size)
       2) Possible exceeding the stack bounds
       3) Compile with "-Wvla-larger-than=size" flag */
    printerr(ENOMEM, 128);
}

void printerr(int errnum, size_t size)
{
    char msg[size]; // instead of alloca(), we use a VLA
    if (errnum == ENOMEM) {
        snprintf(msg, size, "%s", "No memory left");
    } else {
        snprintf(msg, size, "%s", "Unknown error");
    }

    fprintf(stdout, "%s\n", msg);
}

void sizeof_side_effect(void)
{
    size_t size = 12;
    printf("%zu\n", size); // prints 12
    (void)sizeof(int [size++]); // size of array is not known so before calculating it, we must resolve all side effects
    printf("%zu\n", size); // prints 13
    (void)sizeof(int [size++]);
    printf("%zu\n", size); // prints 14
    typedef int foo[size++];
    printf("%zu\n", size); // prints 15
    foo arr;
    printf("%zu\n", sizeof(arr)); // prints 14

    int i = 0;
    int arr2[15] = {0};
    printf("%zu\n", sizeof(arr2)); // prints 15
    printf("%zu : %d\n", sizeof(arr2[i++]), i); // prints 4 and 0; sizeof() calculated size at compile time, so side effects are dismissed
    printf("%zu\n", sizeof(arr2[i++])); // 4
    printf("%d\n", i); // 0
}

void function_prototype_scope_vlas(void)
{
    /* VLAs as function parameters are possible too */

    /* s[] is converted to void *s */
    /* 1. */ void *_memset(void *s, int c, size_t n);
    /* 2. */ /* void *__memset(void s[], int c, size_t n);  Declaration of array of voids is prohibited */
    /* 3. */ void *__memset(char s[], int c, size_t n); // s[] here is demoted to *s
    /* 4. */ void *memset_vla(size_t n, char s[n], int c); // s[] here  is demoted to *s too

    /* 1, 3 and 4 are valid as long as you pass the correct size of array (!) */

    /* VLAs allow us to generalized code */
    int matrix_sum(size_t rows, int m[][4]); // m[rows] is ok too
    int matrix_summ(size_t rows, size_t columns, int [rows][columns]); // a more generalized apporach: rows and columns can be adjusted
}

