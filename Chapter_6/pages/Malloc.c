#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <stdalign.h>
#include <stddef.h>

/* 
    Chapter 6: Dynamically Allocated Memory
        Subchapter: Storage Duration
            1) The Heap and Memory Managers;
            2) When to Use Dynamically Allocated Memory;
        Subchapter: Memory Management Functions
            1) The malloc function (with and w/o declaring a type);
            2) Casting the Pointer to the Type of the Declared Object;
            3) Reading Unitialized Memory;
            4) The malloc Function;
            5) The calloc Function;
            6) The aligned_alloc Function;
            7) The realloc Function;
            8) The reallocArray Function;
            9) The free() function;
            10) Avoiding Memory Leaks;
            11) Avoiding Double Free;
            12) Reading Unitialized Memory; 
    Pages: 99 - 109
*/

void explain_malloc(void);
void explain_calloc(void);
void explain_realloc(void);
void explain_aligned_alloc(void);
void explain_memory(void);
void explain_malloc_without_declaring_a_type(void);
void explain_malloc_when_casting_pointer_to_type_of_declared_object(void);
void reading_unitialized_memory(void);
void explain_free(void);
void explain_double_free(void);

int main(void)
{
    explain_memory();

    return EXIT_SUCCESS;
}

void explain_memory(void)
{
    /* Dynamically allocated storage/memory duration 
     * Extends from the allocation until the deallocation */

    /* It is allocated from the heap which is 1 or more divisible blocks 
     * managed by the memory manager */

    /* The memory manager is responsible for unallocated and deallocated memory */
    /* When it comes to deallocation, it might attached the freed block to the adjacent
     * unallocated free block to make a larger block to reduce fragmentation 
     *
     * It also requests memory blocks from the operating system.
     * */

    /* The memory manager runs alongside the client process */

    /* The memory manager doesn't handle allocated memory
     * It is the caller's responsibility */

    /* dynamically allocated memory is less efficient than static/automatic storage 
     * Because it takes time for the memory manager to find a block of the requested size 
     * It takes time to free the block and possibly re-attach it to the adjacent block too.
     * Generally speaking, switching from the userspace to kernelspace is a taxing endeavor. */

    /* Dynamically allocated memory is used in the following cases: 
     * 1) The size of the storage isn't known at compile time
     * 2) The number of objects isn't known until runtime 
     * Otherwise, use automatic/static storage for higher efficiency. */

    /* Memory leaks are possible too, and they happen 
     * When the allocated storage is not deallocated (malloc() without subsequent free() */

    /* There are a few library functions that manage dynamic memory:
     * 1) malloc();
     * 2) calloc();
     * 3) realloc(); // OpenBSD
     * 4) aligned_alloc(); from C11
     * 5) alloca(); // special case
     * 6) free();
     * */
    explain_malloc();
    explain_aligned_alloc();
    explain_calloc();
    explain_realloc();
    explain_reallocarray();
    explain_free();
    explain_double_free();
}

typedef struct {
    char c[10];
    int i;
    double d;
} widget;

void explain_malloc(void)
{
    /* all memalloc functions accept an arugemnt of type size_t */
    widget *p = malloc(sizeof(widget)); // always use sizeof() when allocating memory (different type sizes on different platforms
    if (p == NULL) { // Handle allocation error
        fprintf(stderr, "failed to allocate memory for widget; cause = %s\n", strerror(errno));
        abort();
    }
    // continue processing
    strncpy(p->c, "Hellscape", sizeof(p->c) - 1);
    p->c[9] = '\0'; // to make sure we properly terminated the string
    p->i = 5;
    p->d = 0.0;

    printf("widget:\n1)name = %s;\n2)i = %d;3)d = %f\n", p->c, p->i, p->d);

    if (p) { // check if p != NULL to avoid double free
        free(p);
        p = NULL; // always assign NULL to the freed pointer (in case of double free)
    }

    /* One cool feature of malloc is allocating memory without declaring a type */
    explain_malloc_without_declaring_a_type();
    explain_malloc_when_casting_pointer_to_type_of_declared_object();
    reading_unitialized_memory();
}

void explain_malloc_without_declaring_a_type(void)
{
    /* Essentially, allocated object does not have an intrinsic type */
    /* So we can make pointers point to any kind of object */
    /* Allocation functions return void * pointer which can be cast to any object */
    void *p = malloc(sizeof(widget));
    char *cp = malloc(sizeof(widget));

    widget w = {
        .c = "abc", 
        .i = 9,
        .d = 3.2
    };

    memcpy(p, &w, sizeof(widget));      // coerced to void * pointers

    /* Contrary to what the book presents, you have to explicitly cast p to widget *p
     * Because accessing an object of type void will generate an error */
    printf("p.i = %d.\n", ((widget *)p)->i);

    /* Or you can assign address to the pointer of the proper type */
    widget *wp = p;
    printf("wp.i = %d.\n", wp->i);
    
    memcpy(cp, &w, sizeof(widget));      // coerced to void * pointers
    /* You also have to cast to widget * here
     * Having sufficient storage for struct widget does not mean char * is widget * */
    printf("cp.i = %d.\n", ((widget *)cp)->i);

#if 0
    /* allocation functions guarantee the strictest alignment requirement */
    void *f = malloc(1); // malloc will allocate more than 1 byte (up to 16 bytes, if there's a 16-byte width typei) Undefined behavior

    /* Please, never write code like that */
    memcpy(f, "more", 15);
    (* (char *)((char *)f + 15)) = '\0';

    printf("f = %s\n", (char *) f);

    if (f) {
        free(f);
        f = NULL;
    }
#endif
    if (cp) {
        free(cp);
        cp = NULL;
    }

    if (p) {
        free(p);
        p = NULL;
    }

}

void explain_malloc_when_casting_pointer_to_type_of_declared_object(void)
{
    /* the cast here is unnecessary */
    /* But explicitly casting void * to the requested type */
    /* Produces useful warnings (misalignment, incorrect requested size, etc.) */
    widget *p = (widget *)malloc(sizeof(widget));

    /* This will produce a warning */
    char *cp = (widget *)malloc(sizeof(widget));

    if (cp) {
        free(cp);
        cp = NULL;
    }

    if (p) {
        free(p);
        p = NULL;
    }
}

void reading_unitialized_memory(void)
{
    void show_the_safe_version(void);
    /* when allocated memory is returned from malloc()
     * It is unitialized (it contains garbage values) */
    char *str = (char *)malloc(16); // allocated memory does not contain zeroes
    if (str) {
        strncpy(str, "123456789abcdef", 15); // the string is not null-terminated
        /* Having zeroed byte at str[15] is just pure luck
         * Because memory manager might allocate more memory than needed
         * This is still undefined behavior */
        printf("str = %s, str[15]=%d\n", str, str[15]);

        str[15] = '\0'; // proper null termination
        free(str);

        show_the_safe_version();
    }
}

void show_the_safe_version(void)
{
    /* when allocated memory is returned from malloc()
     * It is unitialized (it contains garbage values) */
    char *str = (char *)malloc(17); // 0 ... 16
    if (str) {
        strncpy(str, "123456789abcdef", 17); // account for '\0', if src string is less than 17, the rest will be filled with '\0';
        printf("str = %s, str[16]=%d\n", str, str[15]);
        free(str);
    }

}

void explain_aligned_alloc(void)
{
    /* aligned_alloc() is introduced in C11 standard */
    /* If we need stricter alignment, we use this function */
    void *p = aligned_alloc(alignof(max_align_t), 8); // specify alignment requirement and the size of an object
    if (p) { // if alignment is not valid or it doesn't exist, aligned_alloc() will return NULL pointer
        free(p);
        p = NULL;
    }
}


void explain_calloc(void)
{
    /* calloc works like malloc() except for the following things: 
     * 1) the allocated storage is initialized to zero bytes; 
     * 2) it accepts 2 arguments: nmemb and size
     *      nmemb - a number of objects;
     *      size - size of one object
     * 3) the total number of bytes is the product of nmemb * size
     * 4) the function checks for overflow of size_t and returns NULL if true
     * */
    void *p = calloc(2, sizeof(widget));
    if (p) {
        widget arr[2] = {
            {
                .c = "abc",
            },
            {
                .c = "def",
            }
        };
        memcpy(p, arr, sizeof(arr));
        /* Do not overcomplicate your life writing this ugly code */
        printf("p[0]->c = %s, p[0].i = %d, p[1].c = %s, p[1].i = %d\n", (((widget *)p)[0]).c, (((widget *)p)[0]).i, (((widget *)p)[1]).c, (((widget *)p)[0]).i);
    }
}

void explain_realloc(void)
{
    /* realloc() increases/decreases the size of previously allocated storage.
     * If no storage was previously allocated  realloc() calls malloc() */
    void *p = NULL;
    void *p2 = NULL;
    size_t size = 24;
    p2 = realloc(p, 24); // malloc() will be called as p == NULL (no storage)
    p = p2;
    strncpy(p, "123456789abcdef", size);
    printf("p = %s, strlen is %lu, size is %u\n", (char *) p, strlen((char *) p), 16);

    /* When you want to increase the size, the following steps occur:
     * 1) realloc() calls malloc() to allocate new storage of the new size; 
     * 2) realloc() copies contents of the old storage into the new storage;
     * 3) if the new storage is larger, the rest of it remains uninitialized; 
     * 4) realloc() calls free() to free the old storage 
     * 5) if the realloc fails, the old storage is not freed, and realloc() returns NULL
     * 6) By the way, realloc() doesn't check for integer overflow when passing the value size to it */
    
    size+=50;
    
    /* if realloc() fails, then NULL is returned and assigned to p, that previously had old storage */
    /* with the address to the storage lost, the memory leak occurs */
    // p = realloc(p, size); // this will lead to a memory leak
    p2 = realloc(p, size);
    if (size == 0 || (p2 == NULL)) {
        free(p);
        p = NULL;
        return;
    }
    /* At this point, the address of the old p is ivalid, and must not be read */
#if 0
    if (p2 != p) {
        p = p2; // assign p2 to p to store the new address of the storage
    }
#endif
    /* After a successful realloc, always update pointers that previously pointed to the old storage 
     * with p2 that points to the new storage even if the address is the same */
    p = p2;

    if (p) { // allocated
        free(p);
        p = NULL;
    }
}

void explain_reallocarray(void)
{
    /* reallocarray() is identical to realloc() but unlike realloc() it checks for integer overflow */
    void *p = NULL;
    void *p2 = NULL;
    size_t size = 24;
    /* go to arithmetic_operators.c to see how overflow is tested */
    p2 = reallocarray(p, 1, 24); // nmemb * size is calculated to account for possible integer overflow
    p = p2;
    strncpy(p, "123456789abcdef", size);
    printf("p = %s, strlen is %lu, size is %u\n", (char *) p, strlen((char *) p), 16);

    size+=50;
    
    /* Like realloc() if reallocarray() fails (insufficient memory or overflow),
     * reallocarray() returns NULL, and the previous storage is not freed */
    p2 = reallocarray(p, 1, size);
    if (size == 0 || (p2 == NULL)) {
        free(p);
        p = NULL;
        return;
    }
    /* reallocarray() does not initialize new storage with zeroes */
    p = p2;

    if (p) { // allocated
        free(p);
        p = NULL;
    }
}

void explain_free(void)
{
    void *p = NULL;
    void *p2 = NULL;
    size_t size = 24;
    
    p2 = reallocarray(p, 1, 24);
    p = p2;

    strncpy(p, "123456789abcdef", size);
    printf("p = %s, strlen is %lu, size is %u\n", (char *) p, strlen((char *) p), 16);

    size+=50;

    p2 = reallocarray(p, 1, size);
    if (size == 0 || (p2 == NULL)) {
        /* After ever allocation, you are supposed to deallocate the memory */
        /* The system will clean up after the program is terminated */
        /* But if the program works for hours / days / months,  leaking memory will bite you in the ass (running out of memory) */
        /* Memory MUST be reclaimed. */
        free(p);
        p = NULL;

        /* if you set pointer to NULL and call free(), nothing will happen */
        free(p);
        return;
    }

    p = p2;

    if (p) { // allocated
        free(p);
        p = NULL;
    }

    explain_double_free();
}

void explain_double_free(void)
{
#if 0
    {
        /* When freeing the same allocated storage more than once 
         * You may run into double-free vulnerabilities */

        char *p = (char *) malloc(16);
        // ----- snip -----
        free(p);
        /* After the 1st free, the pointer is called a dangling pointer */
        /* Accessing memory that has been freed is undefined behavior */
        /* Writing to freed memory is a security breach, where 
         * Malicious code can be executed */
        *p = 'w'; // writing to / reading from freed memory is undefined behavior 
        free(p); // double free leads to vulnerabilites and exploits
    }
#else
    {
        char *p = (char *) malloc(16);
        // ----- snip -----
        free(p);
        p = NULL;
        /* The sequential invocations of free() are safe */
        free(p); // safe
        free(p); // safe too

        /* Setting pointer to NULL also makes sure that
         * The proigram will crash 100% since accessing
         * the NULL pointer is forbidden */
        *p = 'w'; // crash is guaranteed 
    }
#endif
}