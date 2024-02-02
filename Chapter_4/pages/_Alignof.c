#include <stdio.h>
#include <stdlib.h>
#include <stdalign.h>
#include <stddef.h>
#include <assert.h>

/*
    Chapter 2: Expressions and Operators
        Subchapter: _Alignof Operator
    Page: 76
*/

int main(void)
{
    int arr[4];

    /* this will fail if you write " == 3" because alignment requirement for int is 4 bytes */
    static_assert(_Alignof(arr) == 4, "unexpected alignmnent"); // static assert
    /* this will fail at runtime if you write "== 4" */
    assert(alignof(max_align_t) == 16);// runtime assertion
    printf("Alignment of arr = %zu\n", _Alignof(arr));
    printf("Alignment of max_align_t = %zu\n", alignof(max_align_t));
    return EXIT_SUCCESS;
}
