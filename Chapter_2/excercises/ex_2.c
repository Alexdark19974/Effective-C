#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 3

typedef unsigned int uint;

uint increment(uint *incr_ptr)
{
    return *incr_ptr+=1;
}

uint decrement(uint *decr_ptr)
{
    return *decr_ptr-=1;
}

uint nullify(uint *nullif_ptr)
{
    return *nullif_ptr = 0;
}

int main(int argc, char **argv) {

    uint idx = 0;
    static uint counter = 10;
    enum ops { NULLIFY, INCR, DECR } ops;
    uint (*func_ptr[MAXNUM]) (uint *ptr) = {
        nullify,
        increment,
        decrement,
    };

    while (--argc > 0 && *++argv != NULL) {
        idx = atoi(*argv);
        switch (idx) {
            case NULLIFY:
                printf("Nullify counter\n");
                (*func_ptr[idx])(&counter);
                break;
            case INCR:
                printf("Increment counter\n");
                (*func_ptr[idx])(&counter);
                break;
            case DECR:
                printf("Decrement counter\n");
                (*func_ptr[idx])(&counter);
                break;
        }
    }

    return EXIT_SUCCESS;
}
