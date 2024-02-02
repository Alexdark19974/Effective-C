#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Chapter 2: Object, Functions, and Types
        Subchapter: Derived Types
            1) Pointer Types;
            2) Arrays;
            3) Structs;
            4) Unions;
            5) Functions;
    Pages: 21 - 24
*/

/* struct sigrecord has 4 fields: 1 - 4 bytes; 2 - 20 bytes; 3 - 100 bytes */
struct sigrecord {
    int signum;
    char signame[20];
    char sigdesc[100];
    void (*sig_handler)(int);
} sigline, *sigline_p /* declaring a gloabl struct sigrecord variables */;

void pointer_types(void);
void arrays(int, char **);
void typedefs(void);
void structures(void);
void unions(void);

int main(int argc, char **argv)
{
    /* Derived types are the ones constructed from other types:
     * 1) Pointers;
     * 2) Arrays;
     * 3) Functions;
     * 4) Typedefs;
     * 5) Structures;
     * 6) Unions; */

    pointer_types();
    arrays(argc, argv);
    typedefs();
    structures();
    unions();

    return EXIT_SUCCESS;
}

union {
    struct {
        int type;
    } n;
    struct {
        int type;
        int intnode;
    } ni;
    /* struct nf inside union u 
     * can pack both struct n and struct ni thus,
     * using additional padding, making it 16 bytes */
    struct {
          int type;
          char pad[4]; // the size of union must be a multiple of its largest member (8 bytes)
        double doublenode;
    } nf;
} u;

void unions(void)
{
    /* unions are similar to structs */
    /* the difference is that the memory addresses of the memebers overlap */
    /* Members of a union share the same memory space */

    /* In fact, there is only 1 structure in our union:
     * it can be either: ni or nf;
     * 1) n struct can be packed into ni;
     * 2) ni can be packed into nf;
     * 3) nf has the largest member;
     * 4) 12 bytes + 4 bytes of padding;
     * */
    printf("size of u node is %lu\n", sizeof(u));
    u.nf.type = 0;
    u.nf.doublenode =12384234234234.5;
    /* this will affect u.nf.doublenode since they share the same memory location*/
    u.ni.intnode = 4234234;
    /* all members of n, ni, and nf share the memory location */
    printf("u.n.type =%d\n", u.n.type);
    printf("u.ni.type =%d\n", u.ni.type);
    printf("u.nf.type =%d\n", u.nf.type);

    printf("u.ni.intnode =%d\n", u.ni.intnode);
    printf("u.nf.doublenode =%f\n", u.nf.doublenode);

    printf("size of u node is %lu\n", sizeof(u));
    u.n.type = 0;

    if (u.n.type == 0) {
        puts("union u is intnode");
    } else {
        puts("union u is doublenode");
    }
}

void structures(void)
{
    /* Structures include sequentially allocated member objects */
    sigline.signum = 5; // (.) is a structure member operator
    strcpy(sigline.signame, "SIGINT");
    strcpy(sigline.sigdesc, "Interrupt from keyboard");

    sigline_p = &sigline; // (->) is a structure pointer operator
    sigline_p->signum = 5;
    (*sigline_p).signum = 5; // another way to directly access the structure members
    strcpy(sigline_p->signame, "SIGINT");
    strcpy(sigline_p->sigdesc, "Interrupt from keyboard");
}

void typedefs(void)
{
    /* Use typedef to declare an alias for an existing type */
    /* A new type is not created when typedef is used */
    /* In short, an alias denotes a real type */
    typedef unsigned int uint_type; // uint_type is an alias for unsigned int
    typedef signed char schar_type, *schar_p, (*fp)(void);
    typedef unsigned int (*ptr)(int, int, int);
    /*
     * 1) schar_type is an alias for signed char;
     * 2) schar_p is an  alias for signed char *;
     * 3) fp is an alias for signed char (*)(void);
     * */
    uint_type i = 0;
    schar_type c = 'a';
    schar_p cPtr = NULL;
    fp func_ptr;
    ptr func_func;
}

void pointer_types(void)
{
    /* Type of a pointer is derived from the type of object or function
     * it points to, which is a referenced type */

    int *ip; // (*) is not an operator but a part of declaration of pointer type
    char *cp;
    void *vp;
    int i = 17;

    ip = &i; // & (address-of) operator to generate address of a function or an object;
    printf("ip = %d\n", *ip); // using indirection (*) on ip resolves to the actual object i
}

void func(int arr[5]) {
    static int incr = 0;
    for (int i = 0; i < 5; i++) {
        arr[i] = ++incr;
        printf("arr[%d] = %d\n", i, incr);
    }
    printf("---------------------\n");
}

void from_0_to_9(void)
{
    char str[11]; // arrays are indexed starting at 0: 0 - 10, where 10 is the last element
    for (unsigned int i = 0; i < 10 /* increment till we get to the 10th element */; ++i) {
        str[i] = '0' + i; // subscript operator "[]" allows to access the i-th element of the array
        /* *(str + i) is identical to str[i]; arrays are converted to pointers  */
    }
    printf("%s\n", &str[9]); // &str[9] is the same as str + 9
    str[10] = '\0';
    printf("str = %s\n", str);
}

void arrays(int argc, char **argv)
{
    /* array - a contiguously allocated sequence of objects
     * That all have the same element type */

    unsigned int i = 0;
    unsigned int j = 0;
    /* Do NOT confuse 2D array with a double pointer */
    int arr[3][5]; // array of 3 elements, each of which is an array of 5 elements of type int a.k.a matrix
    float *afp[17]; // array of 17 elements of type pointerto float identified by afp

    from_0_to_9();

    for (int i = 0; i < 3; i++) {
        func(arr[i]);
        /* *(arr + i) works too */
    }

    /* *(arr + i) */
    /* 1) arr is converted to a pointer to the initial array of 5 elements of type int
     *    Starting at arr[i]: arr;
     * 2) i is scaled to the type of arr by multiplying i by the size of one array of
     *    5 int objects: i * (sizeof(*arr)) = 20
     * 3) The results from step 1 and 2 are added: (arr + (i * sizeof(*arr)))
     * 4) Indirection is applied to the result to produce an array of 5 elements of type int: *(arr +i) */
    puts("------------------");
    printf("arr =%p\n", (void *) arr);
    printf("arr =%p\n", (void *) *arr);
    printf("size of arr = %lu\n", sizeof(arr)); // calculating the size of 2-dimensional array
    printf("size of arr[i] = %lu\n", sizeof(*arr)); // calculating the size of the initial array
    printf("size of arr[i][j] = %lu\n", sizeof(**arr));
    printf("value of arr[i][j] =%i\n", *(*(arr + i) + j) /* **arr */);
    puts("------------------");

    int x = arr[i][j]; // j-th element of i-th array
}
