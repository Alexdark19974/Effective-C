#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*
    Chapter 2: Objects, Functions, and Types
        Subchapter: Alignment
    Pages: 18 - 19
*/

struct S {
    int i; double d;  char c; // padding: b b b b | 0 0 0 0 | b b b b b b b b | b | 0 0 0 0 0 0 0 = 24 bytes;
                              // OR padding: b b b b | b b b b b b b b | 0 0 0 0 0 0 0 0 0 0 0
                              // Depends on address boundaries
    // alignemnt occurs according to the object of the biggest size / strictest alignment requirement
    // (double = 8 bytes, so must be divisible by 8)
    // the address of the object is the multiple of object data size
    // the strictest alignment satisifes weaker alignment requirements
};

struct SS {
    double d; int i; char c ; 
    // padding: b b b b b b b b | b b b b | b | 0 0 0 = 16 bytes
    // This is more space effective
    // Repositioning of variables reduced padding by 8 bytes
};

void show_offset_of_fields_in_struct(void)
{
    size_t offset = 0;

    printf("------------- offset of struct S -------------\n");
    offset = offsetof(struct S, c);
    printf("offset of field 'c' in struct S is %lu\n", offset);
    printf("-----------------------------------------------\n");
    
    printf("------------- offset of struct SS -------------\n");
    offset = offsetof(struct SS, c);
    printf("offset of field 'c' in struct SS is %lu\n", offset);
    printf("-----------------------------------------------\n");
}

int main(void)
{
    unsigned char bad_buff[sizeof(struct S)] /*__attribute__((aligned (sizeof(double))))*/ ; // pre-C-11 way of aligning the data at the 8th byte boundary 
    _Alignas(struct S) unsigned char good_buff[sizeof(struct S)]; // C-11 way of aligning data

    struct S *bad_s_ptr = (struct S *)bad_buff;     // wrong pointer alignment
    struct S *good_s_ptr = (struct S *)good_buff;   // correct pointer alignment

/* Well, the first thing that may come as a surprise is that sizeof(S), is actually 24, not 7. Why?
The basic types really want to be placed at the address that is the multiple of their size
That is their alignment requirement. 
So when you have a struct where double (with size of 8) is placed after int (with size of 4),
The whole struct will have alignment requirement of 8 and there will be 4 bytes of padding between the int and double
To ensure that double is placed at an address that is a multiple of 8.
Its size will also be rounded up to a multiple of 8, so the total size is 24.

So when you create a variable of type S, the compiler knows it has to be placed at address that is a multiple of 8.
But when you create an array of chars, they have no alignments requirement and the compiler can place them at an arbitrary address,
Which is exactly what is happening with bad_buff.
On the other hand, when you declare good_buff and say it has the same alignment requirement as S,
The compiler ensures it starts at a multiple of 8 (by leaving some bytes unused),
So it can be accessed as S without breaking the alignment requirements.

So what exactly happens at main? 
Suppose the stack in main starts at address 1004,
So the compiler will place bad_buff of size 24 is starting at address 1004 and ends at 1028.
The problem is that the starting address is not a multiple of 8 and if you access through S* pointer,
The double member is not placed at a multiple of 8, which can have negative consequences,
Like writing it may not be atomic and it can even crash the program on some platforms.
Then the compiler sees the good_buff,
Which requires to be placed at an address that is a multiple of 8 (which is the alignment requirement of S),
So instead of placing it at 1028, the compiler will skip 4 bytes and place it at address 1032 (1008 - 1032), so accessing it through S will work as expected. */

    printf("-----------------------\n");
    printf("size of struct S =%lu\n", sizeof(struct S));
    printf("size of struct SS =%lu\n", sizeof(struct SS));
    printf("-----------------------\n");
    printf("size of bad_buff =%lu\n", sizeof(bad_buff));
    printf("size of good buff =%lu\n", sizeof(good_buff));
    printf("-----------------------\n");
    printf("start address of bad_buff is %p\n", &bad_buff[0]);
    printf("-----------------------\n");

    { 
        bad_s_ptr->i = 14;
        bad_s_ptr->d = 1000000000000000.5;
        bad_s_ptr->c = 'a';
    }
    
    printf("bad_buff_s_ptr=%p\n", (void *) bad_s_ptr);
    printf("bad_s_ptr->i=%i\n", bad_s_ptr->i);
    printf("bad_s_ptr->d=%f\n", bad_s_ptr->d);
    printf("bad_s_ptr->c=%c\n", bad_s_ptr->c);
    printf("---------------------\n");

    /* Unaligned bad_buff[] may not be placed at the address boundary of the multiple of struct S data size */
    /* Access to unaligned data is prone to errors and UB */
    printf("good_buff_s_ptr=%p\n", (void *) good_s_ptr);
    printf("good_s_ptr->i=%i\n", bad_s_ptr->i);
    printf("good_s_ptr->d=%f\n", bad_s_ptr->d);
    printf("good_s_ptr->c=%c\n", bad_s_ptr->c);
    printf("----------------------\n");

    show_offset_of_fields_in_struct();

    return EXIT_SUCCESS;
}

