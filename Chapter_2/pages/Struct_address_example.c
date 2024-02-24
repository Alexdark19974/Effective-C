#include <stdio.h>
#include <stdlib.h>

struct foo3 {
    char *p;
    char c;
    char padded[7];
};

struct foo3 singleton;
struct foo3 quad[4];

struct foo6 {
    short s;
    char c;
    int flip    : 1;
    int nybble  : 4;
    int pad1    : 3;
    int septet  : 7;
    int pad2    :25;
};

struct foo7 {
    int bigfield    : 31; // count here starts from 1, not from 0
    int littlefield : 1;
};

struct foo8 {
    int bigfield1 : 31;
    int littlefield1 : 1;
    int bigfield2 : 31;
    int littlefield2 : 1;
};

struct foo9 {
    int bigfield1 : 31;
    int paddedbitsd1 : 1;
    int bigfield2 : 31;
    int littlefield1: 1;
    int littlefield2:1;
    int paddedbits2: 31;
};

struct foo6 bytes_8;
struct foo7 bytes_4;
struct foo9 bytes_total;

int main(void)
{
    printf("----------------struct singleton---------------------------\n");
    printf("the address of the 1st member of foo3 singleton=%p\n", (void *) &singleton.p);
    printf("the address of the 2nd member of foo3 singleton=%p\n", (void *) &singleton.c);
    printf("the address of the 2nd member of foo3 singleton=%p\n", (void *) &singleton.c);
    printf("the stride address of the padding of foo3 singleton=%p\n", (void *) &singleton.p[2]);
    printf("size of singleton is %lu\n", sizeof(singleton));
    printf("----------------struct singleton---------------------------\n");

    printf("----------------struct foo6--------------------------------\n");
    printf("size of foo6 = %lu\n", sizeof(bytes_8));
    printf("----------------struct foo6--------------------------------\n");

    printf("----------------struct foo7--------------------------------\n");
    printf("size of foo7 = %lu\n", sizeof(bytes_4));
    printf("----------------struct foo7--------------------------------\n");

    printf("----------------struct foo9--------------------------------\n");
    printf("size of foo9 = %lu\n", sizeof(bytes_total));
    printf("----------------struct foo9--------------------------------\n");


    return EXIT_SUCCESS;
}

