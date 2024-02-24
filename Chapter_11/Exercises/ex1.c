#include <stdio.h>
#include <stderr.h>
#include <assert.h>

/* Exercise 1: use the static analyzer to evaluate the defective code
   From Listing 11-1.
   Did the static analysis provide any additional findings? */

struct packed {
    unsigned int i;
    char *p;
};

int main(void) {

    static_assert(
        sizeof(struct packed) == sizeof(unsigned int) + sizeof(char *),
        "struct packed must not have any padding"
    );

    return EXIT_FAILURE;
}

