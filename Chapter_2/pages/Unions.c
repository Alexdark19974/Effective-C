#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

union {
    struct {
        int type;
    } n;
    struct {
        int type;
        int intnode;
    } ni;
    /* struct nf inside union u
       can pack both struct n and struct ni thus,
       using additional padding, making it 16 bytes */
    struct {
        int type;
   //     char pad[4];
        double doublenode;
    } nf;
} u;

typedef unsigned char U8;

typedef union
{
    struct
    {
        U8  A1;
        U8  A2;
        U8  A3;
    };

    struct
    {
        U8  B1;
        U8  B2;
        U8  B3;
    };
} NewUnion;

int main(void)
{
    union u;

    printf("size of union u is %lu\n", sizeof(u));
    printf("size of NewUnionu is %lu\n", sizeof(NewUnion));

    u.n.type = 1;
    u.ni.intnode = 3;
    u.nf.doublenode = 3.14;

    printf("u.nf.doublenode = %f\n"
            "u.n.type=%d\n"
            "u.ni.type=%d\n"
            "u.ni.intnode=%d\n"
            "u.nf.type=%d\n"
            "u.nf.doublenode=%f\n",
            u.nf.doublenode, u.n.type, u.ni.type, u.ni.intnode, u.nf.type, u.nf.doublenode);

     printf("u.nf.doublenode = %p\n"
            "u.n.type=%p\n"
            "u.ni.type=%p\n"
            "u.ni.intnode=%p\n"
            "u.nf.type=%p\n"
            "u.nf.doublenode=%p\n",
            &u.nf.doublenode, &u.n.type, &u.ni.type, &u.ni.intnode, &u.nf.type, &u.nf.doublenode);

    return EXIT_SUCCESS;
}

